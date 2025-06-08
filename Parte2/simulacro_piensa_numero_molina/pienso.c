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
	int numero_pensado;
	int nro_pensado_jugador;
	int done=0;
	


	/* VER
	Jugador jugadores[5]; */

	srand(time(NULL));

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	/*iniciando los threads*/
	/* en este caso no se inician los threads */
	/*for (i=0; i<5; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_PATEADOR+i, MSG_ARQUERO, EVT_INICIO, "");
	}  */

	numero_pensado = generar_numero_random(1, 99);
	printf("El numero que tendran que adivinar es el %d \n", numero_pensado);

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PIENSO, &msg);
	
		if (msg.int_evento == EVT_NUMERO) {
			nro_jugador = msg.int_rte-MSG_JUGADOR;
			nro_pensado_jugador = atoi(msg.char_mensaje);

			printf("Jugador: %d | Adivino numero: %d \n", nro_jugador, nro_pensado_jugador);
			
			if (nro_pensado_jugador == numero_pensado) {
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_PIENSO, EVT_ACERTO, "");
				done = 1;
				printf("\nEl jugador %d ADIVINO!\n", nro_jugador);
			} else {
				enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_PIENSO, EVT_NO_ACERTO, "");
			}
			
		} else {
			printf("Evento desconocido...\n");
		}
		usleep(100*1000);
	}

	printf("Fin del programa\n");	

	return 0;
}

