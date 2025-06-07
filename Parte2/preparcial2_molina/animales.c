#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "funciones.h"
#include "cola.h"
#include "def.h"
#include "thread.h"
#include "global.h"


int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int i;
    int cant_jugadores=3;
    DatosJugador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;

	 
    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_jugadores);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

	datos_thread = (DatosJugador*) malloc(sizeof(DatosJugador)*cant_jugadores);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);


    for (i=0; i<cant_jugadores; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        /*datos_thread[i].pasos_totales = 0; */

        pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
    }


  	for(i=0;i<cant_jugadores;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo el jugador %d \n",datos_thread[i].nro_jugador);
	}

    free(idHilo);
    free(datos_thread);
}

