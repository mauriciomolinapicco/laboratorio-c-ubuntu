#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33
#define CLAVE_BASE_2 55

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_MATO 2
#define EVT_NO_MATO 3
#define EVT_GANA_DOOM 4
#define EVT_GANA_MONST 5

#define MSG_NADIE 0
#define MSG_PANEL 1
#define MSG_JUGADOR 2

#define DOOM 0
#define MONSTRUO 1

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    /*todos van a acceder a la misma variable para saber cuantos metros hizo el humo*/
    int *termino;
    int *numeros_monstruos;
    int numero_doom;
} DatosJugador;

typedef struct {
    int metros_recorridos;
    char nombre[30];
} Jugador;


typedef struct {
    int proceso_1_preparado;
    int proceso_2_preparado;
} Sincronizacion;

#define CANTIDAD_PINOS 10

#endif


