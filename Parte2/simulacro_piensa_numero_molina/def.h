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

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_NUMERO 1
#define EVT_ACERTO 2
#define EVT_NO_ACERTO 3
#define EVT_FINALIZAR 4

#define MSG_NADIE 0
#define MSG_PIENSO 1
#define MSG_JUGADOR 2

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    int cant_jugadores;
} DatosJugador;

typedef struct {
    int tiro;
} Jugador;

#endif

