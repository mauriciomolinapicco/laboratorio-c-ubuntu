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


