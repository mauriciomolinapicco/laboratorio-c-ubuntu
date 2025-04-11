#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char nombre_archivo[20];
    int precio;
    char *menu;

    if (argc != 2) {
        printf("Debes mandar un parametro");
        return 1;
    }
    menu = argv[1];

   switch (toupper(menu[0])) {
    case 'A':
        precio=1000;
        break;
    case 'B':
        precio=2000;
        break;
    case 'C':
        precio=3000;
        break;
    default:
        printf("La opcion ingresada es invalida");
        return 1;
   }

   printf("precio %d", precio);
   sprintf(nombre_archivo, "menu%c.txt", menu[0]);

}