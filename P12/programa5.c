#include <stdio.h>
#define RED "\033[31m"

int main(int argc, char **argv) {
    FILE *archivo = fopen("datos.txt", "r");
    char linea[256];

    if (argc < 2) {
        printf(RED "Error Fatal: hacen falta documentos\n");
        return 1;
    }

    archivo = fopen (argv[1], "r");

if (archivo != NULL)
{
    printf("Archivo abierto correctamente\n");
    char cosa[30];
    float precio;
    while (feof(archivo) == 0) {
        fscanf(archivo, "%s %f", cosa, &precio);
        printf("%s\t%f\n", cosa, precio);
    }
    int res = fclose(archivo);
    printf("fclose: %d\n", res);
}
else
{
    printf(RED "Error fatal: datos.txt no es un archivo o directorio");
}
return 0;
}