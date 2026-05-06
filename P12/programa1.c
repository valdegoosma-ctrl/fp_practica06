#include <stdio.h>
#define RED "\033[31m"

int main() {
    FILE *archivo = fopen("datos.txt", "r");
archivo = fopen("datos.txt", "r");

if (archivo != NULL)
{
    printf("Archivo abierto correctamente\n");
    int res = fclose(archivo);
    printf("fclose: %d\n", res);
}
else
{
    printf(RED "Error fatal: datos.txt no es un archivo o directorio");
}
return 0;
}