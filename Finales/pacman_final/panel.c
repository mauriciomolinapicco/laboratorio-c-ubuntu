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
	int dado;
	int fantasma;
	Jugador jugadores[4];

    Sincronizacion *memoria = NULL;  
	MemoriaJuego *memoria_juego = NULL;

	memoria_juego = (MemoriaJuego*)creo_memoria(sizeof(MemoriaJuego), &id_memoria_juego, CLAVE_BASE_2);    

	memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	memoria_juego->total_metros = 120;
	printf("Panel preparado. Se mando por memoria la cantidad de metros! \n");
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

	strcpy(jugadores[0].nombre, "PACMAN");
	for(i=1;i<4;i++) {
		sprintf(jugadores[i].nombre, "Fantasma %d", i);
	}

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;
		
		mensaje_recibido = atoi(msg.char_mensaje);
		jugadores[nro_jugador].metros_recorridos += mensaje_recibido;

	    switch (msg.int_evento) {
			case EVT_MATA_FANTASMA: {
				sscanf(msg.char_mensaje, "%d|%d", &dado, &fantasma);
				printf("[PANEL] PACMAN sacó %d y se comió al fantasma %d\n", dado, fantasma);
				break;
			}
			
			case EVT_NO_MATA_FANTASMA: {
				sscanf(msg.char_mensaje, "%d", &dado);
				printf("[PANEL] PACMAN sacó %d pero no comió a ningún fantasma.\n", dado);
				break;
			}

			case EVT_NO_MATA_PACMAN: {
				sscanf(msg.char_mensaje, "%d", &dado);
				printf("[PANEL] Fantasma %d sacó %d pero NO le acertó al PACMAN\n", nro_jugador, dado);
				break;
			}

			case EVT_GANA: {
				if (nro_jugador == 0) {
					printf("EL PACMAN MATO A TODOS!\n");
				} else {
					printf("[PANEL] LOS FANTASMAS GANARON, se comieron a PACMAN!\n");	
				}
				done = 1;
				break;
			}
						
			default:
				printf("Evento desconocido \n");
				break;
    	}

		usleep(100*1000);
	}

	liberar_memoria(id_memoria, (char *)memoria);
	liberar_memoria(id_memoria_juego, (char *)memoria_juego);

	printf("Fin del programa\n");	

	return 0;
}

