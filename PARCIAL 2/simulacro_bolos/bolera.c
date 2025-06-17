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
	int cant_pinos_derrubados;
	char msg_enviar_cola[5];
	int id_memoria;
	int id_semaforo;
	int cant_jugadores=2;
	Jugador jugadores[2];

    Sincronizacion *memoria = NULL;  
    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	printf("Bolera preparada\n");
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);

	while(1){
		printf("memoria: %d", memoria->proceso_2_preparado);
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

	/*iniciando los threads*/
	/* en este caso no se inician los threads */

	printf("Iniciando a los jugadores...\n");
	for (i=0; i<cant_jugadores; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_BOLERA, EVT_INICIO, "");
		jugadores[i].cant_tiros=0;
		jugadores[i].pinos_derrubados=0;
		jugadores[i].termino=0;
	}  


	while (jugadores[0].termino==0 || jugadores[1].termino==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_BOLERA, &msg);
	
		if (msg.int_evento == EVT_TIRO) {
			nro_jugador = msg.int_rte-MSG_JUGADOR;
			
			cant_pinos_derrubados = generar_numero_random(0,10-jugadores[nro_jugador].pinos_derrubados);
			if (cant_pinos_derrubados==10 && jugadores[nro_jugador].cant_tiros == 1) {
				cant_pinos_derrubados = 20;
			}
			/*actualizar variables*/
			jugadores[nro_jugador].pinos_derrubados += cant_pinos_derrubados;
			jugadores[nro_jugador].cant_tiros++;

/*		if(cant_pinos_derrubados >= 10 && jugadores[nro_jugador].cant_tiros == 1) {
				printf("CHUZA!\n");
				sprintf(msg_enviar_cola, "%d", 20);
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_FIN, msg_enviar_cola);
				break;
			} */

			printf("Jugador %d | Intento: %d | Derrubo %d pinos | Total: %d\n", nro_jugador, jugadores[nro_jugador].cant_tiros, cant_pinos_derrubados,jugadores[nro_jugador].pinos_derrubados);

			

			/*chequear si el jugador tiro todos los pinos*/
			if (jugadores[nro_jugador].pinos_derrubados >= 10) {
				sprintf(msg_enviar_cola, "%d", jugadores[nro_jugador].pinos_derrubados);
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_FIN, msg_enviar_cola);
				jugadores[nro_jugador].termino = 1;
				printf("\nEl jugador %d derrubo TODOS LOS PINOS!\n", nro_jugador);

				/*chequear si ya tiro 3 veces*/
			} else if (jugadores[nro_jugador].cant_tiros >= 3) {
				sprintf(msg_enviar_cola, "%d", jugadores[nro_jugador].pinos_derrubados);
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_FIN, msg_enviar_cola);
				printf("El jugador %d se quedo sin intentos...\n", nro_jugador);
				jugadores[nro_jugador].termino = 1;

			} else {
				sprintf(msg_enviar_cola, "%d", cant_pinos_derrubados);
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_BOLERA, EVT_RESULTADO, msg_enviar_cola);

			}

		} else {
			printf("Evento desconocido...\n");
		}
		usleep(100*1000);
	}

	liberar_memoria(id_memoria, (char *)memoria);
	printf("Fin del programa\n");	

	return 0;
}

