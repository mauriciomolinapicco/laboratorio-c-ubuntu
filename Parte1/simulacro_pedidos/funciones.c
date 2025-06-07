#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "def.h"
#include "funciones.h"

int generar_numero_random(int min, int max) {
    static int inicializado = 0;
    if (!inicializado) {
        srand(time(NULL));
        inicializado = 1;
    }
    return min + (rand() % (max - min + 1));
}

int generar_cantidad_random() {
    int opciones[3] = {5, 10, 20};
    int indice = generar_numero_random(0, 2);
    return opciones[indice];
}


void generar_pedido(Pedido *pedido) {
    memset(pedido, 0, sizeof(Pedido));
    
    while(1) {
        printf("Ingrese el tipo de menu: A,B,C: ");
        scanf(" %c", &pedido->menu);
        if (toupper(pedido->menu) == 'A' || toupper(pedido->menu) == 'B' || toupper(pedido->menu) == 'C' ) {
            break;
        }
        printf("\nSeleccione una opcion valida! \n");
    }

    while(1) {
        printf("\nQuiere postre? 1 para si, 0 para no\n");
        scanf("%d", &pedido->incluye_postre);
        if (pedido->incluye_postre == 1 || pedido->incluye_postre == 0) {
            break;
        }
        printf("\nSeleccione una opcion valida! \n");
    }

    switch(toupper(pedido->menu)){
        case 'A':
            pedido->precio=1000;
            break;
        case 'B':
            pedido->precio=2000;
            break;
        case 'C':
            pedido->precio=3000;
            break;
        default:
            printf("La opcion ingresada es invalida");
            return;
    }
}
