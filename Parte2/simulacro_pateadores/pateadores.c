#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "funciones.h"
#include "cola.h"
#include "def.h"
#include "thread.h"
#include "global.h"
#include "semaforos.h"
#include "memoria.h"


int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int i;
    int cant_pateadores=5;
    DatosPateador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;

	 
    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_pateadores);

	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	datos_thread = (DatosPateador*) malloc(sizeof(DatosPateador)*cant_pateadores);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);


    for (i=0; i<cant_pateadores; i++)
    {
        datos_thread[i].nro_pateador = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;

        pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
    }


  	for(i=0;i<cant_pateadores;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo el pateador %d \n",datos_thread[i].nro_pateador);
	}

    free(idHilo);
    free(datos_thread);
}

