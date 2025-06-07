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
    int bala_elegida;
    char msg_a_enviar[5];
    int done=0;
    mensaje msg;
    DatosJugador *datos = (DatosJugador*) parametro;
    int *vector = datos->vector_tambor;
    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;



    pthread_mutex_lock(&mutex);
    bala_elegida = generar_numero_random(0,5);

    while(1) {
        if (vector[bala_elegida] != 0) {
            bala_elegida = generar_numero_random(0,5);
        } else {
            /* datos->vector_tambor[bala_elegida] = 1; */
            vector[bala_elegida] = 1;
            break;
        }
    }
    printf("Soy el jugador %d y voy a dispararme con la bala %d\n", nro_jugador, bala_elegida);
    pthread_mutex_unlock(&mutex);
    usleep(500*1000);

    
    while (done==0) {
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
        switch (msg.int_evento) {
            case EVT_INICIO:
                sprintf(msg_a_enviar, "%d", bala_elegida);
                enviar_mensaje(id_cola_mensajes, MSG_REVOLVER, MSG_JUGADOR+nro_jugador, EVT_DISPARO, msg_a_enviar);
                printf("Jugador %d: me dispare con la bala %d\n", nro_jugador, bala_elegida);

            case EVT_SALVADO:
                break;
            case EVT_FIN:
                if (atoi(msg.char_mensaje) == nro_jugador) {
                    printf("Jugador %d: mori\n", atoi(msg.char_mensaje));
                }
                done=1;
                break;
            default:
                break;

        }
    }

    


    pthread_exit ((void *)"Listo");

}

