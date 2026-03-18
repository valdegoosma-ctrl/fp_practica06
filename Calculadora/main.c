#include <stdio.h>

int main()
{
    int a, b, c;
    float f, g, h;
    char op, op2;

    printf("selecciona una opcion\n");
    printf("1. Operaciuones con enteros\n");
    printf("2. Operaciones con reales\n");

    scanf("%c", &op);

    printf("selecciona una opcion\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. multiplicacion\n");
    printf("4. Division\n");
    printf("5. Modulo\n");
    printf("6. Salir\n");
    scanf("&c", &op2);

    if (op == '1')
    {
        printf("Ingresa los dos numeros con los que quieres operar\n");
        scanf("%d %d", &a, &b);
        switch (op2)
        {
        case 1:
            c = a + b;
            break;
        case 2:
            c = -b;
            break;
        case 3:
            c = a * b;
            break;
        case 4:
            c = a / b;
            break;
        case 5:
            c = a % b;
            break;

        default:
            return 0;
        }
        pirntf("El resultado es es %d\n", c);
    }
    else
    {
        switch (op2)
        {
        case 1:
            h = f + g;
            break;
        case 2:
            h = f - b;
            break;
        case 3:
            h = f * g;
            break;
        case 4:
            h = f / g;
            break;
        case 5:
            h = f * g;
            break;

        default:
            return 0;
        }
        pirntf("El resultado es es %d\n", c);
    }
}