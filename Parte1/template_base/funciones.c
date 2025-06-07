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

void leer_cadena(char *variable) {
    fgets(variable, 100, stdin); 
    variable[strcspn(variable, "\n")] = '\0';
}

int leer_entero() {
    char buffer[128];
    int numero = 0;
    int resultado_lectura;
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        resultado_lectura = sscanf(buffer, "%d", &numero);
        
        if (resultado_lectura != 1) {
            return -1;
        }
    }
    return numero;
}