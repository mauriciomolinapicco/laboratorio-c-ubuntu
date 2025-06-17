#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33

/*
Por ahora uso define normal
typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_DISPARO,
    EVT_SALVADO,
    EVT_FIN,
} Mensaje; */

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_CORRO 2
#define EVT_CONTINUO 3
#define EVT_FIN 4

#define MSG_NADIE 0
#define MSG_CANCHA 1
#define MSG_ANIMAL 2

typedef struct {
    int nro_animal;
    int id_cola_mensaje;
} DatosAnimal;

typedef struct {
    int pasos;
    int veces;
    char nombre[30];
} Animal;

#endif

