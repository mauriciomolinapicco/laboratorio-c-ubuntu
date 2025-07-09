#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "def.h"
#include "thread.h"
#include "global.h"
#include "funciones.h"
#include "cola.h"

void *ThreadJugador (void *parametro)
{
    int nro_jugador;
    int id_cola_mensajes;
    mensaje msg;
    int cant_metros_avanzados;
    int *termino;
    DatosJugador *datos = (DatosJugador*) parametro;
    int done=0;
    char pais[30];
    char modelo[30];
    int es_mclaren_o_ferrari;
    char msg_cola[5];
    int metros_avanzados_jugador=0;
    int dado;
    int metros_anteriores;

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    termino = datos->termino;
    es_mclaren_o_ferrari = datos->es_mclaren_o_ferrari;
    strcpy(pais, datos->pais);
    strcpy(modelo, datos->modelo);

    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("[%s: %s] esta iniciando... \n", pais, modelo);
    }
    printf("Se haran %d metros \n", TOTAL_METROS);
    
    while (done==0) {
        pthread_mutex_lock(&mutex);

        if ((*termino) == 1) {
            pthread_mutex_unlock(&mutex);
            usleep(700*1000);
            break;
        } 

        if ((metros_avanzados_jugador / 50) > (metros_anteriores / 50)) { /* condicion cada 50 metros */
            printf("[%s:%s] paso los %d metros... \n", pais, modelo, (metros_avanzados_jugador / 50) * 50);
            printf(" --- BOXES --- \n");

            dado = generar_numero_random(1,3);
            if (dado == 1) {
                printf("Salio 1!! %s pierde un turno! \n", pais);
                printf("***************\n\n");
                pthread_mutex_unlock(&mutex);
                usleep(700*1000);
                continue;
            } else {
                printf("Sigue corriendo!\n");
            }
            printf("***************\n\n");
        }

        /* chequear si choca o no*/
        dado = generar_numero_random(1,2);
        printf("***************\n");
        if(dado == 2){
            printf("%s CHOCO! Pierde la carrera\n", pais);
            printf("***************\n\n");
            pthread_mutex_unlock(&mutex);
            usleep(700*1000);
            break;
        }

        if (es_mclaren_o_ferrari == 1) {
            cant_metros_avanzados = generar_numero_random(6,12);
        } else {
            cant_metros_avanzados = generar_numero_random(5,10);
        }
        metros_anteriores = metros_avanzados_jugador;
        metros_avanzados_jugador += cant_metros_avanzados;

        sprintf(msg_cola, "%d", cant_metros_avanzados);
        printf("Auto %d: [%s: %s] avanza %d metros | Ya lleva %d\n", nro_jugador, pais,modelo, cant_metros_avanzados, metros_avanzados_jugador);
        
        enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);

        if (metros_avanzados_jugador >= TOTAL_METROS) {
            printf("%s GANO CON %d METROS!! \n", pais, TOTAL_METROS);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANO, msg_cola);
            (*termino)=1;
            done=1;
            pthread_mutex_unlock(&mutex);
            usleep(700*1000);
            break;
        }

        pthread_mutex_unlock(&mutex);
        usleep(700*1000);

    }
    
    pthread_exit ((void *)"Listo");

}

