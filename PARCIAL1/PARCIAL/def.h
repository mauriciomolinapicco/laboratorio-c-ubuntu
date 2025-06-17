#ifndef DEF_H
#define DEF_H

#define INTERVALO 100000 /* 100ms en microsegundos */
#define CLAVE_BASE 33
#define ROJO 0
#define VERDE 1
#define LARGO_CADENA 50

#define PRECIO_MT2 2000

typedef struct {
    int id;
    char nombre[50];
    int metros_cuadrados;
    float valor;
    int reservada;
    char apellido_reserva[50];
    int dni_reserva;
} Propiedad;


#endif
