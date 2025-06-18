#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "def.h"
#include "thread.h"
#include "global.h"
#include "funciones.h"
#include "cola.h"

void *ThreadCaja (void *parametro)
{
    int nro_caja;
    int id_cola_mensajes;
    int i;
    char msg_a_cola[5];
    mensaje msg;
    int nro_pensado;
    DatosCaja *datos = (DatosCaja*) parametro;

    nro_caja = datos->nro_caja;
    id_cola_mensajes = datos->id_cola_mensaje;



    while (msg.int_evento != EVT_FINALIZAR) {
        

        pthread_mutex_lock(&mutex);

        nro_pensado = generar_numero_random(1,99);
        printf("Jugador %d | Pienso numero %d \n", nro_caja, nro_pensado);
        sprintf(msg_a_cola, "%d", nro_pensado);

        enviar_mensaje(id_cola_mensajes, MSG_PIENSO, MSG_JUGADOR+nro_caja, EVT_NUMERO, msg_a_cola);

        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_caja, &msg);

        switch (msg.int_evento)
        {
        case EVT_ACERTO:
            printf("Soy el jugador %d y ACERTE!\n", nro_caja);
            for(i=0;i<cant_jugadores;i++) {
                enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_JUGADOR+nro_caja, EVT_FINALIZAR, "");
            }
            break;
        case EVT_NO_ACERTO:
            printf("Soy el jugador %d y le erre...!\n", nro_caja);
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

