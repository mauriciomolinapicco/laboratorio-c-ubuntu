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
	int metros_avanzados_equipo[2];
	int nro_equipo;
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

	strcpy(jugadores[0].nombre, "Batman");
	strcpy(jugadores[1].nombre, "Superman");
	strcpy(jugadores[2].nombre, "Spiderman");
	strcpy(jugadores[3].nombre, "Thor");

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;
		if (nro_jugador < 2) {
			nro_equipo = 0;
		} else {
			nro_equipo = 1;
		}

		mensaje_recibido = atoi(msg.char_mensaje);
		jugadores[nro_jugador].metros_recorridos += mensaje_recibido;
		metros_avanzados_equipo[nro_equipo] += mensaje_recibido;

	    switch (msg.int_evento) {
			case EVT_AVANZO:
				printf("%s avanzo %d pasos | Total: %d | Total del equipo %d: %d\n", jugadores[nro_jugador].nombre, mensaje_recibido, jugadores[nro_jugador].metros_recorridos, nro_equipo, metros_avanzados_equipo[nro_equipo]);
				break;
			
			case EVT_PIERDE_METROS:
				metros_avanzados_equipo[mensaje_recibido] -= METROS_PERDIDOS;
				printf(" --- EVENTO pierde puntos --- \n");
				printf("%s Saco 3!! El equipo %d pierde %d metros!! Ahora tiene %d \n", jugadores[nro_jugador].nombre, mensaje_recibido, METROS_PERDIDOS, metros_avanzados_equipo[mensaje_recibido]);
				break;
			
			case EVT_GANO:
				printf("\nGANO EL EQUIPO %d!!\n", nro_equipo);
				done = 1;
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

