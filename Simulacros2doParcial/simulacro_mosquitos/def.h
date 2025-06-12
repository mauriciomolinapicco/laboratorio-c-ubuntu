#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_AVANZO 2
#define EVT_MUERO 3
#define EVT_ME_SALVO 4
#define EVT_FIN 4

#define MSG_NADIE 0
#define MSG_PANEL 1
#define MSG_JUGADOR 2

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    /*todos van a acceder a la misma variable para saber cuantos metros hizo el humo*/
    int *metros_recorridos_humo; 
    int *terminados;
} DatosJugador;

typedef struct {
    int metros_recorridos;
} Jugador;

typedef struct {
    int proceso_1_preparado;
    int proceso_2_preparado;
} Sincronizacion;

#define CANTIDAD_PINOS 10

#endif

