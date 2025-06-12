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
    DatosJugador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;
    int id_semaforo;
    int id_memoria;
    int cant_vias;
    int total_liberaciones=0;
    Sincronizacion *memoria = NULL;

    if (argc < 2) {
        printf("Se debe mandar de parametro la cantidad de vias \n");
        return 1;
    }

    cant_vias = atoi(argv[1]);
    
    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    
	
	id_semaforo = creo_semaforo();

	espera_semaforo(id_semaforo);
	memoria->proceso_2_preparado=1;
    printf("Vias preparadas\n");
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


    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_vias);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (DatosJugador*) malloc(sizeof(DatosJugador)*cant_vias);

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for (i=0; i<cant_vias; i++)
    {
        datos_thread[i].nro_via = i;
        datos_thread[i].liberaciones_via = 0;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
    }


  	for(i=0;i<cant_vias;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo via: %d | Cant liberaciones: %d \n",datos_thread[i].nro_via, datos_thread[i].liberaciones_via);
        total_liberaciones += datos_thread[i].liberaciones_via;
	}

    printf("En total se liberaron %d vias \n", total_liberaciones);

    free(idHilo);
    free(datos_thread);
    liberar_memoria(id_memoria, (char *)memoria);

    return 0;
}

