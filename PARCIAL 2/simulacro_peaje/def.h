#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_VEHICULOS 2
#define EVT_FINALIZAR 3

#define MSG_NADIE 0
#define MSG_AUTOS 1
#define MSG_VIAS 2

typedef struct {
    int nro_via;
    int id_cola_mensaje;
    int liberaciones_via;
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

