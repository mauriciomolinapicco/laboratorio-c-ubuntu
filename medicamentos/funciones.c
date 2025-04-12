#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

void generar_medicamento(Medicamento *med) {
    memset(med, 0, sizeof(Medicamento)); /* Limpiamos la estructura */
    med->color = generar_numero_random(1, 3); /* 1, 2 o 3 */
    printf("Ingrese la cantidad de pastillas (5, 10 o 20) o presione 0 para aleatorio: ");
    scanf("%d", &med->cantidad);
    if (med->cantidad == 0) {
        med->cantidad = generar_cantidad_random();
        printf("Cantidad generada aleatoriamente: %d\n", med->cantidad);
    } else {
        while (med->cantidad != 5 && med->cantidad != 10 && med->cantidad != 20) {
            printf("Cantidad invalida. Ingrese 5, 10 o 20: ");
            scanf("%d", &med->cantidad);
        }
    }
    asignar_sistema(med);
    snprintf(med->descripcion, MAX_DESC, "Medicamento color %d, sistema %c", med->color, med->sistema);
}

void asignar_sistema(Medicamento *med) {
    if (med->cantidad == 5) {
        med->sistema = 'A';
    } else if (med->cantidad == 10) {
        med->sistema = 'B';
    } else if (med->cantidad == 20) {
        med->sistema = 'C';
    }
}

void mostrar_medicamento(Medicamento *med) {
    printf("Medicamento: %s, Color: %d, Cantidad: %d, Sistema: %c\n",
           med->descripcion, med->color, med->cantidad, med->sistema);
}
