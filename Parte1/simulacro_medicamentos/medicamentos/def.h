#ifndef DEF_H
#define DEF_H

#define INTERVALO 100000 /* 100ms en microsegundos */
#define INTERVALO_PARTIDA 2000
#define CLAVE_BASE 33
#define ROJO 0
#define VERDE 1
#define FILE_NAME "medicamentos.txt"


typedef struct {
    int tipo;
    int color;
    int cantidad;
    char sistema;
} Medicamento;

#endif
