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
	int nro_pateador;
	int tiro;
	int i;
	Pateador pateadores[5];

	srand(time(NULL));

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	/*iniciando los threads*/
	for (i=0; i<5; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_PATEADOR+i, MSG_ARQUERO, EVT_INICIO, "");
	}

	for(i=0;i<5;i++)
	{
		recibir_mensaje(id_cola_mensajes, MSG_ARQUERO, &msg);
		nro_pateador = msg.int_rte-MSG_PATEADOR;

		if (msg.int_evento == EVT_TIRO) {
			printf("Recibi un tiro del pateador %d...\n", nro_pateador);
			tiro = generar_numero_random(EVT_GOL, EVT_FUERA);

			pateadores[nro_pateador].tiro = tiro;
			
			switch (tiro) {
				case EVT_GOL:
					printf("Pateador %d: GOL\n", nro_pateador);
					break;
				case EVT_PALO:
					printf("Pateador %d: PALO\n", nro_pateador);
					break;
				case EVT_TRAVESANO:
					printf("Pateador %d: TRAVESANIO\n", nro_pateador);
					break;
				case EVT_FUERA:
					printf("Pateador %d: AFUERA\n", nro_pateador);
					break;
				default:
					printf("...\n");
					break;
			}
			usleep(500*1000);
			printf("%d\n",tiro);
			enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_ARQUERO, tiro, "");

		} else {
			printf("Evento desconocido...\n");
		}
	}

	printf("Fin de tiros\n");	

	return 0;
}

