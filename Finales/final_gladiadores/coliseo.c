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
	int id_memoria_juego;
	int id_semaforo;
	Jugador jugadores[2];

    Sincronizacion *memoria = NULL;  
	MemoriaJuego *memoria_juego = NULL;

	memoria_juego = (MemoriaJuego*)creo_memoria(sizeof(MemoriaJuego), &id_memoria_juego, CLAVE_BASE_2);    

	memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	memoria_juego->total_pasos = 100;
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
	
	for (i=0; i<2; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_PANEL, EVT_INICIO, "");
		jugadores[i].pasos_recorridos=0;
	}

	/*steve sera jugador 0 y piglin 1*/
	strcpy(jugadores[0].nombre, "Steve");
	strcpy(jugadores[1].nombre, "Piglin");

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;

		mensaje_recibido = atoi(msg.char_mensaje);
		jugadores[nro_jugador].pasos_recorridos += mensaje_recibido;

	    switch (msg.int_evento) {
			case EVT_AVANZO:
				printf("%s avanzo %d pasos | Total: %d\n", jugadores[nro_jugador].nombre, mensaje_recibido, jugadores[nro_jugador].pasos_recorridos);
				break;
			
			case EVT_PASO:
				if (mensaje_recibido==CREEPER) {
					printf("%s paso al CREEPER\n", jugadores[nro_jugador].nombre);
				} else if (mensaje_recibido==ZOMBIE) {
					printf("%s paso al ZOMBIE\n", jugadores[nro_jugador].nombre);
				}
				break;				


			case EVT_MUERO:
				if (mensaje_recibido==CREEPER) {
					printf("%s se murio por un CREEPER\n", jugadores[nro_jugador].nombre);
				} else if (mensaje_recibido==ZOMBIE) {
					printf("%s se murio por un ZOMBIE\n", jugadores[nro_jugador].nombre);
				} else {
					printf("%s se murio\n", jugadores[nro_jugador].nombre);
				}
				
				done=1;
				break;
			
			case EVT_GANO:
				printf("\n%s GANO!!\n", jugadores[nro_jugador].nombre);
				if (nro_jugador == 1) {
					printf("La palmo steve\n");
				}
				done = 1;
				break;

			default:
				printf("Evento desconocido \n");
				break;
    	}

		usleep(300*1000);
	}

	liberar_memoria(id_memoria, (char *)memoria);
	liberar_memoria(id_memoria_juego, (char *)memoria_juego);

	printf("Fin del programa\n");	

	return 0;
}

