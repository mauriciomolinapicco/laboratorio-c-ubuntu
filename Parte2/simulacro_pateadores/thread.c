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
    int nro_pateador;
    int id_cola_mensajes;
    char nombre[20];
    mensaje msg;
    DatosPateador *datos = (DatosPateador*) parametro;

    nro_pateador = datos->nro_pateador;
    id_cola_mensajes = datos->id_cola_mensaje;

    srand(time(NULL));

    pthread_mutex_lock(&mutex);
    usleep(500*1000);
    enviar_mensaje(id_cola_mensajes, MSG_ARQUERO, MSG_PATEADOR+nro_pateador, EVT_TIRO, nombre); 
    
    recibir_mensaje(id_cola_mensajes, MSG_PATEADOR+nro_pateador, &msg);
    printf("evento: %d\n", msg.int_evento);
    if (msg.int_evento == EVT_GOL) {
        printf("GOOOOOOL\n");
    } else {
        printf("UFFFFF\n");
    }

    pthread_mutex_unlock(&mutex);
        
    
    pthread_exit ((void *)"Listo");

}

