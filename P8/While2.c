#include <stdio.h>

int main() {
    int num, sum = 0;
    printf("Ingresa números (0 para terminar):\n");
    scanf("%d", &num);
    while (num != 0) {
        sum += num;
        scanf("%d", &num);
    }
    printf("La suma es: %d\n", sum);
    return 0;
}