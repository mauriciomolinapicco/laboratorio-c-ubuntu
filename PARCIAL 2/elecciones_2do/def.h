#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33
#define CLAVE_BASE_2 55

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_VOTO_PRESIDENTE 2
#define EVT_VOTO_VICE 3

#define MSG_NADIE 0
#define MSG_INICIO 1
#define MSG_VOTANTE 2
#define MSG_PANEL 3

#define CANT_VOTANTES 100

typedef struct {
    int nro_tipo_votante;
    int id_cola_mensaje;
} DatosVotante;

typedef struct {
    int cant_votos;
    char nombre[30];
} Postulante;


typedef struct {
    int proceso_1_preparado;
    int proceso_2_preparado;
} Sincronizacion;


#endif

