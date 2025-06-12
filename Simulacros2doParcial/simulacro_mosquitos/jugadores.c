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
    int cant_jugadores;
    DatosJugador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;
    int id_semaforo;
    int id_memoria;
    int metros_recorridos_humo;
    int terminados;

    Sincronizacion *memoria = NULL;  

    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    
	
	id_semaforo = creo_semaforo();

	espera_semaforo(id_semaforo);
	memoria->proceso_2_preparado=1;
    printf("jugadores preparados\n");
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

    cant_jugadores = 3;

    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_jugadores);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (DatosJugador*) malloc(sizeof(DatosJugador)*cant_jugadores);

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for (i=0; i<cant_jugadores; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        datos_thread[i].metros_recorridos_humo = &metros_recorridos_humo;
        datos_thread[i].terminados = &terminados;
        pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
    }


  	for(i=0;i<cant_jugadores;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo jugador %d ", i);
	}

    free(idHilo);
    free(datos_thread);
    liberar_memoria(id_memoria, (char *)memoria);

    return 0;
}

