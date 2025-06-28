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
    int cant_tipo_votante=2;
    DatosVotante *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;
    int id_semaforo;
    int id_memoria;

    Sincronizacion *memoria = NULL;  

    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();

	espera_semaforo(id_semaforo);
	memoria->proceso_2_preparado=1;
    
    printf("Votantes preparados\n");
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);
	
	while(1){
		espera_semaforo(id_semaforo);
		if(memoria->proceso_1_preparado==1){
			levanta_semaforo(id_semaforo);
            usleep(300 * 1000);
			break;
		} else{
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
		}
	}

    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_tipo_votante);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (DatosVotante*) malloc(sizeof(DatosVotante)*cant_tipo_votante);
 
    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for (i=0; i<cant_tipo_votante; i++)
    {
        datos_thread[i].nro_tipo_votante = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        pthread_create(&idHilo[i], &atributos, ThreadVotante, &datos_thread[i]);
    }


  	for(i=0;i<cant_tipo_votante;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo hilo de votante: %d \n", i);
	}

    free(idHilo);
    free(datos_thread);
    liberar_memoria(id_memoria, (char *)memoria);

    return 0;
}

