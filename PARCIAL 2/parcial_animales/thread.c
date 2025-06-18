#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "thread.h"
#include "def.h"
#include "global.h"
#include "mensajes.h"
#include "memoria.h"
#include "funciones.h"

void *ThreadJugador (void *parametro)
{
	/*DECLARACION DE VARIABLES*/
	int nro_animal;
	int id_cola_mensajes;
	int done=0;
	char cadena[50+1];
	int min_pasos;
	int max_pasos;
	int pasos;
	char nombre[50+1];
	tthread *datos_thread;
	mensaje	msg;
	
	/*INICIO DEL CUERPO DEL PROGRAMA*/
	datos_thread = (tthread*)parametro;
	nro_animal = datos_thread->nro_animal;
	id_cola_mensajes = datos_thread->id_colamensaje;
	sprintf(&nombre[0], "%s", datos_thread->nombre);
	min_pasos = datos_thread->min_pasos;
	max_pasos = datos_thread->max_pasos;
	

	srand(time(NULL));

	pthread_mutex_lock(&mutex);
	recibir_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, &msg);
	printf("%s listo!\n", nombre);
	pthread_mutex_unlock(&mutex);
	usleep(ESPERA * 1000);
		
	if(msg.int_evento == EVT_INIT){
		while(done==0)
		{
			pthread_mutex_lock(&mutex);
			pasos = inDevolverAleatorio(min_pasos, max_pasos);

			memset(&cadena[0], 0x00, sizeof(cadena));
			sprintf(cadena, "%d", pasos);

			printf("Soy %s y avanzo %d pasos\n", nombre, pasos);

			enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_ANIMAL+nro_animal, EVT_AVANZO, cadena);
			recibir_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, &msg);
	
			switch(msg.int_evento){
				case EVT_CONTINUAR:
					break;
				case EVT_FIN:
					printf("SOY EL ANIMAL %s Y TERMINE LA CARRERA...\n", nombre);
					done = 1;
				break;
				default:
					printf("Se ha recibido un evento inesperado!");
				break;
			}
			pthread_mutex_unlock(&mutex);
			usleep(600 * 1000);
		};
	}
	sleep (1);
	pthread_exit ((void *)"Listo");
}

