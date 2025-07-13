#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33
#define CLAVE_BASE_2 55

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_MATA_FANTASMA 2
#define EVT_NO_MATA_FANTASMA 3
#define EVT_GANA 4
#define EVT_NO_MATA_PACMAN 5
#define EVT_PIERDE_TURNO 6

#define MSG_NADIE 0
#define MSG_PANEL 1
#define MSG_JUGADOR 2

#define BATMAN 0
#define SUPERMAN 1
#define SPIDERMAN 2
#define THOR 3


#define METROS_PERDIDOS 5

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    /*todos van a acceder a la misma variable para saber cuantos metros hizo el humo*/
    int *termino;
    int *numeros_fantasmas;
    int *fantasmas_muertos;
    int nro_pacman;
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

#define CANTIDAD_PINOS 10

#endif


