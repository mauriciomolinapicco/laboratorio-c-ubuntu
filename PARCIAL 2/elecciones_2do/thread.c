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

void *ThreadVotante (void *parametro)
{
    int nro_tipo_votante;
    int id_cola_mensajes;
    mensaje msg;
    DatosVotante *datos = (DatosVotante*) parametro;
    int cant_votos=0;
    char nombre[20];
    char candidato_1[25];
    char candidato_2[25];
    char msg_cola[5];
    int voto;

    nro_tipo_votante = datos->nro_tipo_votante;
    id_cola_mensajes = datos->id_cola_mensaje;

    if (nro_tipo_votante == 0) {
        strcpy(nombre, "Presidente");
        strcpy(candidato_1, "Senior MS");
	    strcpy(candidato_2, "Senior MI");
    } else {
        strcpy(nombre, "Vicepresidente");
        strcpy(candidato_1, "Senior A");
	    strcpy(candidato_2, "Seniora V");

    }
    
    recibir_mensaje(id_cola_mensajes, MSG_VOTANTE+nro_tipo_votante, &msg);
    if (msg.int_evento == EVT_INICIO) {
        printf("Votacion para %s esta iniciando... \n", nombre);
    }
    
    while (cant_votos < CANT_VOTANTES) {
        pthread_mutex_lock(&mutex);

        voto = generar_numero_random(0,1);
        cant_votos++;
        sprintf(msg_cola, "%d", voto);
        if (voto == 0) {
            printf("Votante %d para %s => %s\n", cant_votos, nombre, candidato_1);
        } else {
            printf("Votante %d para %s => %s\n", cant_votos, nombre, candidato_2);
        }
        
        
        if (nro_tipo_votante == 0) {
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_VOTANTE+nro_tipo_votante, EVT_VOTO_PRESIDENTE, msg_cola); 
        } else {
            enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_VOTANTE+nro_tipo_votante, EVT_VOTO_VICE, msg_cola); 
        }
           

        pthread_mutex_unlock(&mutex);
        usleep(200*1000);

    }
    
    
    pthread_exit ((void *)"Listo");

}

