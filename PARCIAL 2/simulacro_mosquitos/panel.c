#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "funciones.h"
#include "cola.h"
#include "def.h"
#include "semaforos.h"
#include "memoria.h"


int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    mensaje msg;
	int nro_jugador;
	int done=0;
	int i;
	int cant_metros_avanzados;
	char msg_enviar_cola[5];
	int id_memoria;
	int id_semaforo;
	int cant_jugadores=3;
	Jugador jugadores[2];
	char nombre[20];

    Sincronizacion *memoria = NULL;  
    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	printf("panel preparado\n");
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);

	while(1){
		espera_semaforo(id_semaforo);
		if(memoria->proceso_2_preparado==1){
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
			break;
		} else{
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
		}
	}
	
	srand(time(NULL));

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	
	for (i=0; i<cant_jugadores; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_PANEL, EVT_INICIO, "");
		jugadores[i].metros_recorridos=0;
	}  

	while (done < 2)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;

		memset(nombre, 0, sizeof(nombre)); /*limpio para q no quede sucia*/
		if (msg.int_rte == MSG_JUGADOR+0) {
			strcpy(nombre, "Humo");
		} else {
			sprintf(nombre, "Mosquito %d", nro_jugador);
		}

		cant_metros_avanzados = atoi(msg.char_mensaje);
		jugadores[nro_jugador].metros_recorridos += cant_metros_avanzados;

	    switch (msg.int_evento) {
			case EVT_AVANZO:
				printf("%s avanzo %d metros | Total: %d\n", nombre, cant_metros_avanzados, jugadores[nro_jugador].metros_recorridos);
				break;
			case EVT_MUERO:
				printf("%s se murio\n", nombre);
				done++;
				break;
			case EVT_ME_SALVO:
				printf("%s se salvo! 3\n", nombre);
				done++;
				break;
			default:
				printf("Evento desconocido \n");
				break;
    	}

		usleep(100*1000);
	}

	liberar_memoria(id_memoria, (char *)memoria);
	printf("Fin del programa\n");	

	return 0;
}

