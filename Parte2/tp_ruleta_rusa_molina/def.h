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
#define EVT_DISPARO 2
#define EVT_SALVADO 3
#define EVT_FIN 4

#define MSG_NADIE 0
#define MSG_REVOLVER 1
#define MSG_JUGADOR 2

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    int *vector_tambor;
} DatosJugador;


#endif

