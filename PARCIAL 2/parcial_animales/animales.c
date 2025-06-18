#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "def.h"
#include "global.h"
#include "mensajes.h"
#include "memoria.h"
#include "funciones.h"
#include "thread.h"
#include "semaforo.h"


int main(int argc, char *argv[])
{
	int id_cola_mensajes;
	int i = 0;
	int *listo = NULL;
	int id_memoria;
	int id_semaforo;
	pthread_attr_t 	atributos;
	tthread *datos_thread;
	pthread_t* idHilo;

	listo = (int *)creo_memoria(sizeof(int), &id_memoria);
	
	id_semaforo = creo_semaforo();
	
	espera_semaforo(id_semaforo);
	(*listo)++;
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);
	
	while(TRUE){
		espera_semaforo(id_semaforo);
		if(*listo == 2){
			levanta_semaforo(id_semaforo);
			break;
		} else{
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
		}
	}

	idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*CANTIDAD);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	pthread_mutex_init(&mutex, NULL);
	
	datos_thread = (tthread*) malloc(sizeof(tthread)*CANTIDAD);

	id_cola_mensajes = creo_id_cola_mensajes();

	/*inicializo la estructura de animales*/
	for(i=0; i<CANTIDAD; i++){
		memset(datos_thread[i].nombre, 0x00, sizeof(datos_thread[i].nombre));
	}
	sprintf(datos_thread[0].nombre, "%s", "Conejo");
	datos_thread[0].min_pasos = 4;
	datos_thread[0].max_pasos = 9;

	sprintf(datos_thread[1].nombre, "%s", "Gato");
	datos_thread[1].min_pasos = 1;
	datos_thread[1].max_pasos = 10;

	sprintf(datos_thread[2].nombre, "%s", "Perro");
	datos_thread[2].min_pasos = 3;
	datos_thread[2].max_pasos = 8;
	
	/*lanzo threads*/
	for(i=0; i<CANTIDAD; i++)
	{
		datos_thread[i].nro_animal = i;
		datos_thread[i].id_colamensaje = id_cola_mensajes;
		pthread_create (&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
	}

	for(i=0;i<CANTIDAD;i++)
	{
		pthread_join(idHilo[i], NULL);
	}
	/*libero memoria*/
	free(idHilo);
	free(datos_thread); 
	liberar_memoria(id_memoria, (char *)listo);
	return 0;
}
