#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33
#define CLAVE_BASE_2 55

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_BOXES 1
#define EVT_AVANZO 2
#define EVT_NO_AVANZO 3
#define EVT_CHOCO 3
#define EVT_GANO 5
#define EVT_EMPATE 6
#define EVT_FIN 7


#define MSG_NADIE 0
#define MSG_PANEL 1
#define MSG_JUGADOR 2

#define TOTAL_METROS 295
#define CANTIDAD_AUTOS 10 

typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
    /*todos van a acceder a la misma variable para saber cuantos metros hizo el humo*/
    int *termino;
    char pais[30];
    char modelo[30];
    int es_mclaren_o_ferrari;
} DatosJugador;

typedef struct {
    char pais[30];
    char modelo[30];
    int es_mclaren_o_ferrari;
    int metros_recorridos;
    int choco;
} Auto;

typedef struct {
    Auto autos[10];
} MemoriaAutos;

typedef struct {
    int proceso_1_preparado;
    int proceso_2_preparado;
} Sincronizacion;

#define CANTIDAD_PINOS 10

#endif


