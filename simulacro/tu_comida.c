#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "archivos.h"
#include "def.h"

int main (int argc, char *argv[])
{
    char menu;
    char postre;
    char cadena[100];
    char nombre_archivo[20];
    int cant_pedidos=0;

    while(1)
    {
        while(1)
        {
            printf("Elegi el menu: A,B,C: ");
            scanf(" %c", &menu);
            if (toupper(menu) =='A' || toupper(menu) == 'B' || toupper(menu) == 'C')
            {
                break;
            }
            printf("Seleccione una opcion valida");
        }
        while(1)
        {
            printf("Quiere con postre? ($200 adicionales) y/n ");
            scanf(" %c", &postre);
            if (toupper(postre) =='Y' || toupper(postre) == 'N')
            {
                break;
            }
            printf("\nSeleccione una opcion valida\n");
        }

        memset(nombre_archivo,0,sizeof(nombre_archivo));
        sprintf(nombre_archivo, "menu%c.txt",toupper(menu));

        if (abrirArchivo(nombre_archivo, "w") == 0)
        {
            printf("\nError al abrir el archivo\n");
            continue;
        }
        printf("Menu seleccionado: %c\n", menu);
        printf("Postre seleccionado: %c\n", postre);

        sprintf(cadena, "MENU %c - POSTRE: %c\n", menu, postre);
        printf("Cadena generada: %s\n", cadena);
        escribirArchivo(cadena);
        cerrarArchivo();

        cant_pedidos++;/*por ahora no lo uso para nada*/

    }
    
}