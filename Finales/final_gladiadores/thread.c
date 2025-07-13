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
    int cant_pasos_avanzados;
    int total_pasos_juego;
    int *termino;
    DatosJugador *datos = (DatosJugador*) parametro;
    int done=0;
    char nombre[20];
    char msg_cola[5];
    int pasos_avanzados_jugador=0;

    int zombie_flag=0;
    int creeper_flag=0;
    int dado; /*variable con la q va a pelear*/

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    termino = datos->termino;
    total_pasos_juego = datos->total_pasos;

    /* variable compartida entre ambos threads */
    (*termino) = 0;

    /* el 0 va a ser el steve y 1 piglin*/
    if (nro_jugador == 0) {
        strcpy(nombre, "Steve");
    } else {
        strcpy(nombre, "Piglin");
    }

    
    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("%s esta iniciando... \n", nombre);
    }
    
    while (done==0) {
        pthread_mutex_lock(&mutex);

        if ((*termino) == 1) {
            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
            break;
        } 
        /*STEVE*/
        if (nro_jugador == 0) {

            cant_pasos_avanzados = generar_numero_random(2,8);
            pasos_avanzados_jugador += cant_pasos_avanzados;
            sprintf(msg_cola, "%d", cant_pasos_avanzados);
            printf("%s avanzo %d pasos | Total: %d\n", nombre, cant_pasos_avanzados, pasos_avanzados_jugador);
            
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);

            if (pasos_avanzados_jugador >= total_pasos_juego) {
                printf("Steve se salvo!! \n");
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANO, msg_cola);
                (*termino)=1;
                done=1;
            }

            /*caso zombie*/
            if (pasos_avanzados_jugador >= 20 && zombie_flag == 0){
                zombie_flag=1;
                printf("\nLe toca con el zombie... Si sale 4 muere\n");
                dado = generar_numero_random(1,4);
                printf("Le salio el %d \n", dado);
                sprintf(msg_cola, "%d", ZOMBIE);
                if (dado == NUMERO_ZOMBIE) {
                    printf("MURIO STEVE!!\n");
                    enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_MUERO, msg_cola);
                    (*termino) = 1;
                    done = 1;
                } else {
                    printf("Se salvo! \n");
                    enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_PASO, msg_cola);
                }
                printf("\n");

            } 

            /*caso creeper*/
            else if (pasos_avanzados_jugador >= 45 && creeper_flag == 0) {
                creeper_flag=1;
                printf("\nLe toca con el creeper... Si sale 3 muere\n");
                dado = generar_numero_random(1,3);
                printf("Le salio el %d \n", dado);
                sprintf(msg_cola, "%d", CREEPER);
                if (dado == NUMERO_CREEPER) {
                    printf("MURIO STEVE!!\n");
                    enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_MUERO, msg_cola);
                    (*termino) = 1;
                    done = 1;
                } else {
                    printf("Se salvo! \n");
                    enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_PASO, msg_cola);
                }
                printf("\n");
            }

        /*PIGLI*/    
        } else {
            cant_pasos_avanzados = generar_numero_random(1,6);
            pasos_avanzados_jugador += cant_pasos_avanzados;
            printf("%s avanzo %d pasos | Total: %d\n", nombre, cant_pasos_avanzados, pasos_avanzados_jugador);
            sprintf(msg_cola, "%d", cant_pasos_avanzados);

            if (pasos_avanzados_jugador >= total_pasos_juego) {
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANO, msg_cola);
                printf("Gano PIGLI con %d pasos... Se muere STEVE\n", pasos_avanzados_jugador);
                done=1;
                (*termino)=1; 
            }
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);
        }
        

        pthread_mutex_unlock(&mutex);
        usleep(500*1000);

    }
    
    
    pthread_exit ((void *)"Listo");

}

