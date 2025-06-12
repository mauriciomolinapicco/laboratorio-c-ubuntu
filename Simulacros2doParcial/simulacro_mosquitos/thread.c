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
    int cant_jugadores;
    mensaje msg;
    int cant_metros_avanzados;
    int *metros_recorridos_humo;
    int *terminados;
    int total_metros=0;
    DatosJugador *datos = (DatosJugador*) parametro;
    int done=0;
    char nombre[20];
    char msg_cola[5];

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    metros_recorridos_humo = datos->metros_recorridos_humo;
    terminados = datos->terminados;

    (*terminados) = 0;

    /* el 0 va a ser el proceso humo y los otros mosquitos*/
    if (nro_jugador == 0) {
        strcpy(nombre, "Humo");
    } else {
        sprintf(nombre, "Mosquito %d", nro_jugador);
    }

    
    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("%s esta iniciando... \n", nombre);
    }
    
    while (done==0) {
        pthread_mutex_lock(&mutex);
        
        if (nro_jugador == 0) {
            if ((*terminados) >= 2) {
                break;
            }
            cant_metros_avanzados = generar_numero_random(1,4);
            sprintf(msg_cola, "%d", cant_metros_avanzados);
            (*metros_recorridos_humo) += cant_metros_avanzados; 
            printf("%s avanzo %d metros | Total: %d \n", nombre, cant_metros_avanzados, (*metros_recorridos_humo));
            
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);
            pthread_mutex_unlock(&mutex);
            usleep(300*1000);
            continue;
        } else {
            cant_metros_avanzados = generar_numero_random(3,6);
            sprintf(msg_cola, "%d", cant_metros_avanzados);
            total_metros += cant_metros_avanzados;
            
            printf("%s avanzo %d metros | Total: %d \n", nombre, cant_metros_avanzados, total_metros);

            if (total_metros >= 95) {
                printf("%s se SALVO!\n", nombre);
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_ME_SALVO, msg_cola);
                (*terminados)++;
                done=1;
            }
            else if ((*metros_recorridos_humo) >= total_metros) {
                printf("%s se MURIO!! \n", nombre);
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_MUERO, msg_cola);
                (*terminados)++;
                done=1;
            } else {
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);
            }
        }
        

        pthread_mutex_unlock(&mutex);
        usleep(300*1000);

    }
    
    
    pthread_exit ((void *)"Listo");

}

