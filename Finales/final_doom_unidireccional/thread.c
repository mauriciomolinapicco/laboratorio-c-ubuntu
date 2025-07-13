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
    DatosJugador *datos = (DatosJugador*) parametro;
    char nombre[20];
    char msg_cola[20];
    int numero_aleatorio;
    int i;
    int flag;
    int nro_doom;
    int monstruos_muertos=0;

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;
    termino = datos->termino;
    nro_doom = datos->numero_doom;

    if(nro_jugador == 0) {
        strcpy(nombre, "DOOM");
        printf("%s: mi numero es %d \n",nombre, nro_doom);
    } else {
        sprintf(nombre, "Monstruo %d", nro_jugador);
        printf("%s: mi numero es %d \n",nombre, datos->numeros_monstruos[nro_jugador]);
    }
    

    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("%s esta iniciando... \n", nombre);
    }
    
    while (1) {
        pthread_mutex_lock(&mutex);

        if (nro_jugador != 0) {
            if (datos->numeros_monstruos[nro_jugador] == 0) {
                printf("%s: MORI... saliendo...\n");
                pthread_mutex_unlock(&mutex);
                usleep(500*1000);
                break;
            }
        }
        

        if ((*termino) == 1) {
            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
            break;
        }

        printf("===================\n");
        

        if (nro_jugador == DOOM) {
            numero_aleatorio = generar_numero_random(1,15);
            printf("Tiro de %s ====> %d | ", nombre, numero_aleatorio);
            sprintf(msg_cola, "%d", numero_aleatorio);

            flag = 0;
            for (i=1;i<4;i++) {
                if (datos->numeros_monstruos[i-MONSTRUO] == 0) {
                    continue;
                }
                if (numero_aleatorio == datos->numeros_monstruos[i-MONSTRUO]) {
                    printf("Le acerte al monstruo %d \n", i);
                    datos->numeros_monstruos[i-MONSTRUO] = 0;
                    flag=1;
                    monstruos_muertos++;
                    sprintf(msg_cola, "%d|%d", i, numero_aleatorio);
                    enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_MATO, msg_cola);
                }
            }
            if (flag == 0) {
                printf("No le pegue a ninguno! \n");
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_NO_MATO, msg_cola);
            }

            /*chequea si mato a todos*/
            if (monstruos_muertos == 3) {
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANA_DOOM, "");
                (*termino) = 1;
                pthread_mutex_unlock(&mutex);
                usleep(500*1000);
                break;
            }
            /* caso monstruo */
        } else {            
            numero_aleatorio = generar_numero_random(1,50);
            printf("Tiro de %s ====> %d | ", nombre, numero_aleatorio);
            sprintf(msg_cola, "%d", numero_aleatorio);

            if (numero_aleatorio == nro_doom) {
                printf(" Le pegue a DOOM!!\n");
                printf("Ganan los monstruos!!\n");
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_GANA_MONST, msg_cola);
                (*termino)=1;
                pthread_mutex_unlock(&mutex);
                usleep(500*1000);
                break;
            } else {
                printf("Le erre a DOOM!\n");
                enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+nro_jugador, EVT_NO_MATO, msg_cola);
            }
        }
        printf("===================\n");
    
        pthread_mutex_unlock(&mutex);
        usleep(500*1000);

    }
        
    pthread_exit ((void *)"Listo");

}

