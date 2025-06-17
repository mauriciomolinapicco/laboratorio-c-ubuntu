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
    int nro_animal;
    int id_cola_mensajes;
    int pasos_realizados;
    int pasos_max;
    int pasos_min;
    char msg_a_enviar[5];
    int done=0;
    char nombre[20];
    mensaje msg;
    DatosAnimal *datos = (DatosAnimal*) parametro;

    nro_animal = datos->nro_animal;
    id_cola_mensajes = datos->id_cola_mensaje;

    /*cada animal tiene una cantidad especifica de pasos maximos y minimos*/
    switch (nro_animal) {
        case 0:
            pasos_max = 9;
            pasos_min = 4;
            sprintf(nombre, "%s", "Conejo");
            break;
        case 1:
            pasos_max = 10;
            pasos_min = 1;
            sprintf(nombre, "%s", "Gato");
            break;
        case 2:
            pasos_max = 8;
            pasos_min = 3;
            sprintf(nombre, "%s", "Perro");
            break;
        default:
            break;
    }

    pthread_mutex_lock(&mutex);
    recibir_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, &msg);
    pthread_mutex_unlock(&mutex);
    usleep(300*1000);

    if (msg.int_evento == EVT_INICIO) {
        enviar_mensaje(id_cola_mensajes, MSG_CANCHA, MSG_ANIMAL+nro_animal, EVT_INICIO, nombre); 
        while (done==0) {
            pthread_mutex_lock(&mutex);

            pasos_realizados = generar_numero_random(pasos_min, pasos_max);
            sprintf(msg_a_enviar, "%d", pasos_realizados);
            printf("Soy el %s y corro %d pasos \n", nombre, pasos_realizados);

            enviar_mensaje(id_cola_mensajes, MSG_CANCHA, MSG_ANIMAL+nro_animal, EVT_CORRO, msg_a_enviar); 
            recibir_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, &msg);
            
            
            switch (msg.int_evento) {
                case EVT_CONTINUO:
                    break;
                case EVT_FIN:
                    printf("Soy el %s y termine la carrera\n", nombre);
                    done=1;
                    break;
                default:
                    printf("Evento no esperado...\n");
                    break;
            }

            pthread_mutex_unlock(&mutex);
            usleep(500*1000);
        }
    }

    
    
    pthread_exit ((void *)"Listo");

}

