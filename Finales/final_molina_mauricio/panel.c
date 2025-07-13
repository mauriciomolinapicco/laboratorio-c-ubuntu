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
	int cantidad_peces_muertos=0;
	Jugador jugadores[CANTIDAD_JUGADORES];

    Sincronizacion *memoria = NULL;
	MemoriaJuego *memoria_juego = NULL;

	memoria_juego = (MemoriaJuego*)creo_memoria(sizeof(MemoriaJuego), &id_memoria_juego, CLAVE_BASE_2);

	memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	memoria_juego->total_metros = 130;
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
	
	for (i=0; i<CANTIDAD_JUGADORES; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_PANEL, EVT_INICIO, "");
		jugadores[i].metros_recorridos=0;
	}

    strcpy(jugadores[0].nombre, "Pez 1");
    strcpy(jugadores[1].nombre, "Pez 2");
    strcpy(jugadores[2].nombre, "Pez 3");
    strcpy(jugadores[3].nombre, "Tiburon");
    strcpy(jugadores[4].nombre, "Pulpo 1");
    strcpy(jugadores[5].nombre, "Pulpo 2");

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;

		mensaje_recibido = atoi(msg.char_mensaje);
		jugadores[nro_jugador].metros_recorridos += mensaje_recibido;

	    switch (msg.int_evento) {
			case EVT_AVANZO:
				/* el char mensaje es la cantidad de metros avanzados */
				printf("[%s] avanzo %d metros | Total: %d \n", jugadores[nro_jugador].nombre, mensaje_recibido, jugadores[nro_jugador].metros_recorridos);
				break;
			
			case EVT_COMO:
				/* el char mensaje es el id del pez que se comio */
				printf("\n --- [%s] COMIO A: %s --- \n", jugadores[nro_jugador].nombre, jugadores[mensaje_recibido].nombre);
				cantidad_peces_muertos++;
				printf("Ya van %d peces muertos...\n", cantidad_peces_muertos);
				if (cantidad_peces_muertos >= 3) {
					printf("Ya no queda ni uno, se murieron todos...\n");
					done=1;
				}
				break;
			
			case EVT_GANO:
				printf("--- [%s] LLEGO A LA META!! --- \n", jugadores[nro_jugador].nombre);
				if (nro_jugador >= 3) {
					printf("Se mueren los peces...\n");
				}
				done=1;
				break;
				
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

