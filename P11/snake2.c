#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#define WIDTH 30
#define HEIGHT 15
int score


int snakeX, snakeY; // posición de la primera parte de la vibora
int fruitX, fruitY;
char direction = 'd';

void increaseScore() {
    static int score = 0;
    score++;
    printf("Score: %d\n", score);
}
void moveSnake(int *x, int *y, char dir) {
switch (dir)
{
    case 'w': case 'W': (*y)--; break;
    case 's': case 'S': (*y)++; break;
    case 'a': case 'A': (*x)--; break;
    case 'd': case 'D': (*x)++; break;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}   

#ifdef _WIN32 // funcion para no presionar enter
 char readInput() {
    if (_kbhit()) {
        return _getch();
    }
    return direction;
#else 
char readImput() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_GETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        return ch;
    }
    return direction;   
}
#endif

int x, y; // posición de la primera parte de la vibora
int fruitX, fruitY;
char input;

/**
 * Función que sirve  para iniciar el juego
 */
void setup(){
    snakeX=WIDTH/2;
    snakeY=HEIGHT/2;

    fruitX = rand()%(WIDTH-2)+1;
    fruitY = rand()%(HEIGHT-2)+1;

    score = 0;
}

void draw(){
    system("clear");
    for(int i=0; i<HEIGHT;i++){
        for(int j=0; j< WIDTH; j++){
            if(j==0 || i ==0 || i==HEIGHT-1 || j == WIDTH-1){
                 printf("#");
                 continue;
            }
            if(snakeX==j && snakeY==i){
                printf("s");
                continue;
            } 
            if(fruitX==j && fruitY==i){
                printf("f");
                continue;
            } 
            printf(" ");
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
    printf("Presiona W o S o D o A\n");
}

void logic(){
        }   
    if (snakeX<0 || snakeX>=WIDTH || snakeY<0 || snakeY>=HEIGHT){
        printf("Game Over\n");
        exit(0);
    }

    if(snakeX==fruitX && snakeY==fruitY){
        score++;
        fruitX = rand()%WIDTH;
        fruitY = rand()%HEIGHT;
 
   }
    if (snakeX==fruitX && snakeY==fruitY){
        fruitX = rand()%WIDTH;
        fruitY = rand()%HEIGHT;
        increaseScore();
    }
}
int main (){
    setup();
    while(true){
        draw();
        direction = readInput();
        moveSnake(&snakeX, &snakeY, direction);
        logic();
        #ifdef _WIN32
        Sleep(150);
        #else 
        usleep(150000);
        #endif  
    }
    return 0;
}
int main(){
    setup();
    while(true){
        draw();
        inputFunc();
        logic();
    }
    return 0;
}
