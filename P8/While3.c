#include <stdio.h>

int main() {
    int num, pos = 0, neg = 0;
    printf("Ingresa números (0 para terminar):\n");
    scanf("%d", &num);
    while (num != 0) {
        if (num > 0) pos++;
        else if (num < 0) neg++;
        scanf("%d", &num);
    }
    printf("Números positivos: %d\n", pos);
    printf("Números negativos: %d\n", neg);
    return 0;
}