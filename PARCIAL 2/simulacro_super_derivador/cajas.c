#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
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
    int cant_cajas;
   	int id_memoria;
	int id_semaforo;
   	Producto *listo = NULL;
    DatosCaja *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;

    if (argc < 2) {
        printf("Debe mandar el parametro de cantidad de jugadores\n");
        return 1;
    }

    cant_cajas = 3;
	
    listo = (Producto *)creo_memoria(sizeof(Producto) * 20, &id_memoria, CLAVE_BASE);

    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_cajas);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (DatosCaja*) malloc(sizeof(DatosCaja)*cant_cajas);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for (i=0; i<cant_cajas; i++)
    {
        datos_thread[i].nro_caja = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;

        pthread_create(&idHilo[i], &atributos, ThreadCaja, &datos_thread[i]);
    }


  	for(i=0;i<cant_cajas;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo la %d \n",datos_thread[i].nro_caja);
	}

    free(idHilo);
    free(datos_thread);
}

