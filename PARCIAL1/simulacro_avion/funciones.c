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

int leer_string(char *destino, int tamanio, const char *mensaje) {
    if (destino == NULL || tamanio <= 0) {
        return 0;
    }
    
    if (mensaje != NULL) {
        printf("%s", mensaje);
    }
    
    if (fgets(destino, tamanio, stdin) == NULL) {
        return 0;
    }
    
    int len = 0;
    while (destino[len] != '\0' && destino[len] != '\n') {
        len++;
    }
    
    if (destino[len] == '\n') {
        destino[len] = '\0';
    }
    
    return 1;
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
