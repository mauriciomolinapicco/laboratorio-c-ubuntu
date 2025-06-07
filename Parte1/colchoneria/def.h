#ifndef DEF_H
#define DEF_H

#define INTERVALO 100000 /* 100ms en microsegundos */
#define CLAVE_BASE 33
#define ROJO 0
#define VERDE 1
#define LARGO_CADENA 50


typedef struct
{
    int codigo;
    int cantidad;
    char nombre[LARGO_CADENA];
} Descripcion;

#endif
