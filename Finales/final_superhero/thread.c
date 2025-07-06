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
    int nro_equipo;
    int cant_metros_avanzados;
    int total_metros_juego;
    int *termino;
    int *pierde_turno;
    DatosJugador *datos = (DatosJugador*) parametro;
    int done=0;
    char nombre[20];
    char msg_cola[5];
    int metros_avanzados_jugador=0;
    int *metros_avanzados_equipo;
    int dado;
    int metros_anteriores;
    int otro_equipo;

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    nro_equipo = datos->nro_equipo;
    pierde_turno = datos->pierde_turno;
    termino = datos->termino;
    strcpy(nombre, datos->nombre_jugador);
    total_metros_juego = datos->total_metros;
    metros_avanzados_equipo = datos->metros_avanzados_equipo;


    /* variable compartida entre ambos threads */
    (*termino) = 0;

    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("%s esta iniciando... (Equipo %d) \n", nombre, nro_equipo);
    }
    printf("Se haran %d metros \n", total_metros_juego);
    
    while (done==0) {
        pthread_mutex_lock(&mutex);

        if ((*termino) == 1) {
            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
            break;
        } 

        if((*pierde_turno) == nro_equipo) {
            printf("%s: ME HICIERON PERDER UN TURNO!\n", nombre);
            (*pierde_turno)=-1;
            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
            continue;
        }

        if (nro_jugador == 0 || nro_jugador == 2) {
            cant_metros_avanzados = generar_numero_random(1,7);
        } else {
            cant_metros_avanzados = generar_numero_random(2,8);
        }
        metros_anteriores = metros_avanzados_jugador;
        metros_avanzados_jugador += cant_metros_avanzados;
        metros_avanzados_equipo[nro_equipo] += cant_metros_avanzados;

        sprintf(msg_cola, "%d", cant_metros_avanzados);
        printf("%s avanzo %d metros | Ya lleva %d | El equipo %d va %d pasos\n", nombre, cant_metros_avanzados, metros_avanzados_jugador, nro_equipo, metros_avanzados_equipo[nro_equipo]);
        
        enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);

        if (metros_avanzados_equipo[nro_equipo] >= total_metros_juego) {
            printf("Gano el equipo %d!! \n", nro_equipo);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANO, msg_cola);
            (*termino)=1;
            done=1;
            pthread_mutex_unlock(&mutex);
            usleep(200*1000);
            break;
        }

        if ((metros_avanzados_jugador / 10) > (metros_anteriores / 10)) {
            printf("%s paso los %d metros y puede tirar el dado para lanzar poder \n", nombre, (metros_avanzados_jugador / 10) * 10);
            printf(" --- TIRA DADO --- \n");
            otro_equipo = 0;
            if (nro_equipo == 0) {
                otro_equipo = 1;
            }
            dado = generar_numero_random(1,3);
            if (dado == 1) {
                printf("1!! Pierde un turno! \n");
                (*pierde_turno)=otro_equipo;
            } else if (dado == 3) {
                printf("3!! El equipo %d pierde %d metros \n", otro_equipo, METROS_PERDIDOS);
                metros_avanzados_equipo[otro_equipo] -= METROS_PERDIDOS;
                sprintf(msg_cola, "%d", otro_equipo);
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_PIERDE_METROS, msg_cola);
            } else {
                printf("Saco 2!! No pasa nada\n");
            }
        }


        pthread_mutex_unlock(&mutex);
        usleep(500*1000);

    }
    
    
    pthread_exit ((void *)"Listo");

}

