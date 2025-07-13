#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33
#define CLAVE_BASE_2 55

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_AVANZO 2
#define EVT_COMO 3
#define EVT_GANO 4

#define MSG_NADIE 0
#define MSG_PANEL 1
#define MSG_JUGADOR 2

#define CANTIDAD_JUGADORES 6
#define CANTIDAD_PECES 3

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    /*todos van a acceder a las mismas variables*/
    int *termino;
    int *cantidad_peces_muertos;
    int total_metros;
    char nombre_jugador[20];
    int *metros_avanzados;
    int *peces_muertos;
} DatosJugador;

typedef struct {
    int metros_recorridos;
    char nombre[30];
} Jugador;

typedef struct {
    int total_metros;
} MemoriaJuego;

typedef struct {
    int proceso_1_preparado;
    int proceso_2_preparado;
} Sincronizacion;


#endif


