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
    int pasos_realizados;
    char msg_a_enviar[5];
    int done=0;
    int total_pasos=0;
    int vueltas=0;
    mensaje msg;
    DatosJugador *datos = (DatosJugador*) parametro;
    char *animales[] = {"Conejo", "Gato", "Perro"};
    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;

    
    while (done==0) {
        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);

        pthread_mutex_lock(&mutex);

        switch (msg.int_evento) {
            case EVT_CORRO:
                vueltas += 1;
                switch(nro_jugador) {
                    case 0:
                        pasos_realizados = generar_numero_random(4,9);
                        total_pasos += pasos_realizados;
                        printf("%d Conejo: corrio %d pasos | Acumulado: %d | Vueltas: %d\n", nro_jugador, pasos_realizados, total_pasos, vueltas);
                        break;
                    case 1:
                        pasos_realizados = generar_numero_random(1,10);
                        total_pasos += pasos_realizados;
                        printf("%d Gato: corri %d pasos | Acumulado: %d | Vueltas: %d\n", nro_jugador, pasos_realizados, total_pasos, vueltas);
                        break;
                    case 2:
                        pasos_realizados = generar_numero_random(3,8);
                        total_pasos += pasos_realizados;
                        printf("%d Perro: corri %d pasos | Acumulado: %d | Vueltas: %d\n", nro_jugador, pasos_realizados, total_pasos, vueltas);
                        break;
                    default:
                        printf("algo salio mal.....\n");
                        break;
                }
                sprintf(msg_a_enviar, "%d", pasos_realizados);
                enviar_mensaje(id_cola_mensajes, MSG_CANCHA, MSG_JUGADOR+nro_jugador, EVT_CORRO, msg_a_enviar);
                break;
            case EVT_FIN:
                printf("%s: %d pasos | %d vueltas. Saliendo... \n", animales[nro_jugador], total_pasos, vueltas);
                done=1;
                break;
            default:
                break;

        }
        pthread_mutex_unlock(&mutex);
        usleep(INTERVALO*1000);
    }

    
    pthread_exit ((void *)"Listo");
    return 0;

}

