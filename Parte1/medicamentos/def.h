#ifndef DEF_H
#define DEF_H

#define MAX_DESC 50
#define CANT_MEDICAMENTOS 3
#define INTERVALO 100000 /* 100ms en microsegundos */
#define CLAVE_BASE 33
#define ROJO 0
#define VERDE 1

typedef struct {
    int color;          /* 1: Rojo, 2: Amarillo, 3: Fucsia */
    int cantidad;       /* 5, 10 o 20 */
    char sistema;       /* A, B o C */
    char descripcion[MAX_DESC]; /* Descripción del medicamento */
} Medicamento;

#endif
