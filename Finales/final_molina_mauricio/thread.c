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
    int total_metros_juego;
    int *termino;
    int *cantidad_peces_muertos;
    DatosJugador *datos = (DatosJugador*) parametro;
    int done=0;
    char nombre[20];
    char msg_cola[5];
    int dado;
    int i;
    int cota_max;
    int cota_min;
    int distancia;
    int distancia_para_comer;

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    termino = datos->termino;
    cantidad_peces_muertos = datos->cantidad_peces_muertos;
    strcpy(nombre, datos->nombre_jugador);
    total_metros_juego = datos->total_metros;

    if (nro_jugador == 4 || nro_jugador == 5) { /*pulpos*/
        cota_min=1;
        cota_max=3;
        distancia_para_comer=10;
    } else if (nro_jugador == 3) { /*tiburon*/
        cota_min=1;
        cota_max=8;
        distancia_para_comer=7;
    } else {
        cota_min=1;
        cota_max=6;
    }

    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("%s esta iniciando... \n", nombre);
        usleep(400*1000);
    }
    
    
    while (done==0) {
        pthread_mutex_lock(&mutex);

        if ((*termino) == 1) {
            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
            break;
        }

        printf("------------------\n");

        if (nro_jugador < 3) {
            /* para los peces chequeo si estan vivos o muertos*/
            if (datos->peces_muertos[nro_jugador] == 1) {
                printf("%s: ME MORI!!\n", nombre);
                pthread_mutex_unlock(&mutex);
                usleep(500*1000);
                break;
            }
        }

    
        cant_metros_avanzados = generar_numero_random(cota_min, cota_max);
        datos->metros_avanzados[nro_jugador] += cant_metros_avanzados;
        
        printf("[%s] avanzo %d metros | Lleva %d \n", nombre, cant_metros_avanzados, datos->metros_avanzados[nro_jugador]);
        sprintf(msg_cola, "%d", cant_metros_avanzados);
        enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_AVANZO, msg_cola);

        /* chequear si llega a la meta */
        if (datos->metros_avanzados[nro_jugador] >= total_metros_juego) {
            printf("[%s] LLEGO A LA META!! \n", nombre);
            if (nro_jugador >= 3) {
                printf("Infelizmente los peces perecen...\n");
            } else {
                printf("VAMOOO los peces se salvaron (al menos uno je)\n");
            }

            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANO, "");
            (*termino)=1;
            done=1;
            pthread_mutex_unlock(&mutex);
            usleep(200*1000);
            break;
        }

        /* caso tiburon o pulpo que pueden comer/danar a los otros */
        if (nro_jugador >= 3) {
            dado = generar_numero_random(1,3);
            if (dado == 1) {
                printf("[%s] ME SALIO 1... vamos a ver a quien como... \n", nombre);
                for (i=0;i<CANTIDAD_PECES;i++) {
                    if (datos->peces_muertos[i] == 0) {
                        distancia = abs(datos->metros_avanzados[nro_jugador] - datos->metros_avanzados[i]);
                        if (distancia <= distancia_para_comer) {
                            printf("\t[%s] mato al pez %d que estaba a %d metros de mi \n", nombre, i, distancia);
                            datos->peces_muertos[i] = 1;
                            (*cantidad_peces_muertos)++;
                            sprintf(msg_cola, "%d", i);
                            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_COMO, msg_cola);
                        } else {
                            printf("\t[%s] no me pude comer al pez %d que estaba a %d metros...\n", nombre, i, distancia);
                        }
                    } 
                }
            } else {
                printf("[%s] me salio %d... se salvaron esta vez \n", nombre, dado);
            }
            
        }
        
        if ((*cantidad_peces_muertos) >= 3) {
            (*termino)=1;
            done=1;
            printf("Se murieron todos los peces! Perecieron.... \n");
        }

        
        printf("------------------\n");
        pthread_mutex_unlock(&mutex);
        usleep(1000*1000);

    }
    
    usleep(700 * 1000);
    pthread_exit ((void *)"Listo");

}

