#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33
#define INTERVALO 500

#define EVT_NINGUNO 0
#define EVT_CORRO 1
#define EVT_FIN 2


#define MSG_NADIE 0
#define MSG_CANCHA 1
#define MSG_JUGADOR 2

/*
#define MSG_JUGADOR1 2
#define MSG_JUGADOR2 3
#define MSG_JUGADOR3 4
*/


typedef struct {
    int nro_jugador;
    int id_cola_mensaje;
} DatosJugador;


#endif

