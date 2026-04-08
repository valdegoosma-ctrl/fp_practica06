#include <stdio.h>

int main() {
    int num, sum = 0;
    printf("Ingresa números (0 para terminar):\n");
    do {
        scanf("%d", &num);
        if (num != 0) sum += num;
    } while (num != 0);
    printf("La suma es: %d\n", sum);
    return 0;
}
        {
        }