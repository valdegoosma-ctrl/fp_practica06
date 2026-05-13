#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#define MAX_BULLETS 50
#define MAX_ENEMIES 20
#define MAX_STARS 8

int playerX, playerY;
int score = 0;
bool game_over = false;
bool paused = false;

int bulletX[MAX_BULLETS];
int bulletY[MAX_BULLETS];
bool bulletActive[MAX_BULLETS];

int enemyX[MAX_ENEMIES];
int enemyY[MAX_ENEMIES];
bool enemyActive[MAX_ENEMIES];

int starX[MAX_STARS];
int starY[MAX_STARS];
bool starActive[MAX_STARS];

int enemySpeedCounter = 0;
int starSpeedCounter = 0;

#ifdef _WIN32
char readInput() {
    if (_kbhit()) return _getch();
    return 0;
}
#else
struct termios oldt;

void enableRawMode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char readInput() {
    int ch = getchar();
    if (ch != EOF) return ch;
    return 0;
}
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void setup() {
    srand(time(NULL));

    playerX = WIDTH / 2;
    playerY = HEIGHT - 3;

    for (int i = 0; i < MAX_BULLETS; i++) {
        bulletActive[i] = false;
    }

    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemyActive[i] = false;
    }

    for (int i = 0; i < MAX_STARS; i++) {
        starActive[i] = false;
    }
}

void shootBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bulletActive[i]) {
            bulletX[i] = playerX;
            bulletY[i] = playerY - 2;
            bulletActive[i] = true;
            break;
        }
    }
}

void generateEnemy() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemyActive[i]) {
            enemyX[i] = (rand() % (WIDTH - 2)) + 1;
            enemyY[i] = 1;
            enemyActive[i] = true;
            break;
        }
    }
}

void generateStar() {
    for (int i = 0; i < MAX_STARS; i++) {
        if (!starActive[i]) {
            starX[i] = (rand() % (WIDTH - 2)) + 1;
            starY[i] = 1;
            starActive[i] = true;
            break;
        }
    }
}

bool isPlayerAt(int x, int y) {
    if (x == playerX && y == playerY - 1) return true;
    if (x == playerX - 1 && y == playerY) return true;
    if (x == playerX && y == playerY) return true;
    if (x == playerX + 1 && y == playerY) return true;
    if (x == playerX && y == playerY + 1) return true;
    return false;
}

void drawPlayerPart(int x, int y) {
    if (x == playerX && y == playerY - 1) {
        printf(BLUE "^");
    } 
    else if (x == playerX - 1 && y == playerY) {
        printf(BLUE "/");
    } 
    else if (x == playerX && y == playerY) {
        printf(BLUE "A");
    } 
    else if (x == playerX + 1 && y == playerY) {
        printf(BLUE "\\");
    } 
    else if (x == playerX && y == playerY + 1) {
        printf(BLUE "V");
    }
}

void draw() {
    bool printed;
    clearScreen();

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printed = false;

            if (j == 0 || i == 0 || i == HEIGHT - 1 || j == WIDTH - 1) {
                printf(YELLOW "▒");
                continue;
            }

            if (isPlayerAt(j, i)) {
                drawPlayerPart(j, i);
                continue;
            }

            for (int b = 0; b < MAX_BULLETS; b++) {
                if (bulletActive[b] && bulletX[b] == j && bulletY[b] == i) {
                    printf(GREEN "|");
                    printed = true;
                    break;
                }
            }

            if (printed) continue;

            for (int s = 0; s < MAX_STARS; s++) {
                if (starActive[s] && starX[s] == j && starY[s] == i) {
                    printf(YELLOW "*");
                    printed = true;
                    break;
                }
            }

            if (printed) continue;

            for (int e = 0; e < MAX_ENEMIES; e++) {
                if (enemyActive[e] && enemyX[e] == j && enemyY[e] == i) {
                    printf(RED "V");
                    printed = true;
                    break;
                }
            }

            if (printed) continue;

            printf(RESET " ");
        }

        printf(RESET "\n");
    }

    printf(RESET "Score: %d\n", score);

    if (paused) {
        printf(YELLOW "PAUSA ACTIVADA\n" RESET);
    }

    printf("A/D = mover | ESPACIO = disparar | P = pausa | Q = salir\n");
}

void movePlayer(char input) {
    if (input == 'p' || input == 'P') {
        paused = !paused;
        return;
    }

    if (input == 'q' || input == 'Q') {
        game_over = true;
        return;
    }

    if (paused) return;

    if ((input == 'a' || input == 'A') && playerX > 2) {
        playerX--;
    } 
    else if ((input == 'd' || input == 'D') && playerX < WIDTH - 3) {
        playerX++;
    } 
    else if (input == ' ') {
        shootBullet();
    }
}

void updateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bulletActive[i]) {
            bulletY[i]--;

            if (bulletY[i] <= 0) {
                bulletActive[i] = false;
            }
        }
    }
}

void updateEnemies() {
    static int spawnCounter = 0;

    spawnCounter++;

    if (spawnCounter % 3 == 0) {
        generateEnemy();
    }

    enemySpeedCounter++;

    if (enemySpeedCounter >= 3) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemyActive[i]) {
                enemyY[i]++;

                if (enemyY[i] >= HEIGHT - 1) {
                    enemyActive[i] = false;
                }

                if (isPlayerAt(enemyX[i], enemyY[i])) {
                    game_over = true;
                }
            }
        }

        enemySpeedCounter = 0;
    }
}

void updateStars() {
    static int starSpawnCounter = 0;

    starSpawnCounter++;

    if (starSpawnCounter % 18 == 0) {
        generateStar();
    }

    starSpeedCounter++;

    if (starSpeedCounter >= 4) {
        for (int i = 0; i < MAX_STARS; i++) {
            if (starActive[i]) {
                starY[i]++;

                if (starY[i] >= HEIGHT - 1) {
                    starActive[i] = false;
                }

                if (isPlayerAt(starX[i], starY[i])) {
                    starActive[i] = false;
                    score += 5;
                }
            }
        }

        starSpeedCounter = 0;
    }
}

void checkCollisions() {
    for (int b = 0; b < MAX_BULLETS; b++) {
        if (!bulletActive[b]) continue;

        for (int e = 0; e < MAX_ENEMIES; e++) {
            if (!enemyActive[e]) continue;

            if (bulletX[b] == enemyX[e] && bulletY[b] == enemyY[e]) {
                bulletActive[b] = false;
                enemyActive[e] = false;
                score++;
                break;
            }
        }

        for (int s = 0; s < MAX_STARS; s++) {
            if (!starActive[s]) continue;

            if (bulletX[b] == starX[s] && bulletY[b] == starY[s]) {
                bulletActive[b] = false;
                starActive[s] = false;
                score += 5;
                break;
            }
        }
    }
}

void logic() {
    if (paused) return;

    updateBullets();
    updateEnemies();
    updateStars();
    checkCollisions();
}

int main() {
    char input;

    setup();

#ifndef _WIN32
    enableRawMode();
#endif

    while (!game_over) {
        draw();

        input = readInput();
        movePlayer(input);

        logic();

#ifdef _WIN32
        Sleep(60);
#else
        usleep(60000);
#endif
    }

#ifndef _WIN32
    disableRawMode();
#endif

    clearScreen();

    printf(RED "GAME OVER\n" RESET);
    printf("Score final: %d\n", score);

    return 0;
}