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
    int *termino;
    int nro_pacman;
    DatosJugador *datos = (DatosJugador*) parametro;
    int done=0;
    int dado;
    int i;
    char msg_cola[20];
    int evento;
    int mato=0;
    int muertos=0;

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    nro_pacman = datos->nro_pacman;
    termino = datos->termino;

    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        if (nro_jugador == 0) {
            printf("Iniciando Pacman");
        } else {
            printf("Iniciando Fantasma %d\n", nro_jugador);
        }
    }
    
    while (done==0) {
        pthread_mutex_lock(&mutex);
        
        if ((*termino) == 1) {
            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
            break;
        }

        if (nro_jugador != 0) {
            if (datos->fantasmas_muertos[nro_jugador-1] == 1) {
                printf("Murio el fantasma %d ... \n", nro_jugador);
                pthread_mutex_unlock(&mutex);
                usleep(500*1000);
                done=1;
                break;
            }
        }

        /* caso pacman */
        if(nro_jugador == 0) {
            dado = generar_numero_random(1,30);
            printf("***[PACMAN] saque %d ***\n", dado);
            mato=0;
            for(i=0;i<3;i++) {
                if (datos->numeros_fantasmas[i] == dado) {
                    datos->fantasmas_muertos[i] = 1;
                    printf("VAMOOOO mate al fantasma %d \n", i+1);
                    sprintf(msg_cola, "%d|%d", dado,i+1);
                    enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_MATA_FANTASMA, msg_cola);
                    mato = 1;
                    muertos++;
                }
            }
            if (mato == 0) {
                printf("No mato a nadie!!\n");
                sprintf(msg_cola, "%d", i+1);
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_NO_MATA_FANTASMA, "");
            }
            printf("***FIN RONDA DE PACMAN***\n");
            if (muertos >= 3) {
                printf("El PACMAN mato a todos!!!! GANADORRRRR\n");
                (*termino) = 1;
                done=1;
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANA, "");
            }
        } else {
            dado = generar_numero_random(1,100);
            printf("[Fantasma %d] saque %d \n", nro_jugador, dado);
            if (dado == nro_pacman) {
                printf("Le ACERTE al PACMAN \n");
                printf("GANAMOS LOS FANTASMAS! \n");
                (*termino) = 1;
                done=1;
                evento=EVT_GANA;
            } else {
                evento=EVT_NO_MATA_PACMAN;
            }
            sprintf(msg_cola, "%d", dado);
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, evento, "");
        }

        

    
        pthread_mutex_unlock(&mutex);
        usleep(500*1000);

    }
        
    pthread_exit ((void *)"Listo");

}

