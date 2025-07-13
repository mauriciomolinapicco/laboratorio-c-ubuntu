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
	int done=0;
	int i;
	int nro_jugador;
	int mensaje_recibido;
	int id_memoria;
	int id_semaforo;
	Jugador jugadores[4];
	int id_monstruo;

    Sincronizacion *memoria = NULL;  

	memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	printf("Panel preparado! \n");
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
	
	for (i=0; i<4; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_PANEL, EVT_INICIO, "");
		jugadores[i].metros_recorridos=0;
	}

	strcpy(jugadores[0].nombre, "DOOM");
	strcpy(jugadores[1].nombre, "Monstruo 1");
	strcpy(jugadores[2].nombre, "Monstruo 2");
	strcpy(jugadores[3].nombre, "Monstruo 3");

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;

		mensaje_recibido = atoi(msg.char_mensaje);
		jugadores[nro_jugador].metros_recorridos += mensaje_recibido;

	    switch (msg.int_evento) {
			case EVT_NO_MATO:
				if (nro_jugador == DOOM) {
					printf("[DOOM] disparó pero no mató a ningún monstruo.\n");
				} else {
					printf("[%s] disparó pero falló contra DOOM.\n", jugadores[nro_jugador].nombre);
				}
				break;
			
			case EVT_MATO:
				sscanf(msg.char_mensaje, "%d|%d", &id_monstruo, &mensaje_recibido);
				printf("[DOOM] saco %d mato al %s \n", mensaje_recibido, jugadores[id_monstruo].nombre);
				break;
			
			case EVT_GANA_DOOM:
				done=1;
				printf("%s hizo que el equipo rival pierda un turno!\n", jugadores[nro_jugador].nombre);
				break;
			
			case EVT_GANA_MONST:
				printf("[%s] Saco %d y mato a DOOM! \n", jugadores[nro_jugador+MONSTRUO].nombre, mensaje_recibido);
				printf("GANARON LOS MONSTRUOS! \n");
				done = 1;
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

