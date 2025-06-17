#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_TIRO 2
#define EVT_RESULTADO 3
#define EVT_FIN 4

#define MSG_NADIE 0
#define MSG_BOLERA 1
#define MSG_JUGADOR 2

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    int cant_puntos;
} DatosJugador;

typedef struct {
    int cant_tiros;
    int pinos_derrubados;
    int termino;
} Jugador;

typedef struct {
    int proceso_1_preparado;
    int proceso_2_preparado;
} Sincronizacion;

#define CANTIDAD_PINOS 10

#endif

