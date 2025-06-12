#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "def.h"
#include "thread.h"
#include "global.h"
#include "funciones.h"
#include "cola.h"

void *ThreadJugador (void *parametro)
{
    int nro_jugador;
    int id_cola_mensajes;
    int cant_jugadores;
    int i;
    char msg_a_cola[5];
    mensaje msg;
    int nro_pensado;
    DatosJugador *datos = (DatosJugador*) parametro;

    nro_jugador = datos->nro_jugador;
    cant_jugadores = datos->cant_jugadores;
    id_cola_mensajes = datos->id_cola_mensaje;



    while (msg.int_evento != EVT_FINALIZAR) {
        

        pthread_mutex_lock(&mutex);

        nro_pensado = generar_numero_random(1,99);
        
        sprintf(msg_a_cola, "%d", nro_pensado);

        enviar_mensaje(id_cola_mensajes, MSG_PIENSO, MSG_JUGADOR+nro_jugador, EVT_NUMERO, msg_a_cola);

        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);

        switch (msg.int_evento)
        {
        case EVT_ACERTO:
            printf("Jugador %d, pienso el numero %d |  ACERTE!\n", nro_jugador, nro_pensado);
            for(i=0;i<cant_jugadores;i++) {
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_JUGADOR+nro_jugador, EVT_FINALIZAR, "");
            }
            break;
        case EVT_NO_ACERTO:
            printf("Jugador %d, pienso el numero %d |  ERRE!\n", nro_jugador, nro_pensado);
            break;

        case EVT_FINALIZAR:
            break;
        
        default:
            printf("evento desconocido\n");
            break;
        }

        pthread_mutex_unlock(&mutex);
        usleep(500*1000);
    }
    
    
    pthread_exit ((void *)"Listo");

}

