#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "cola.h"
#include "def.h"


int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    mensaje msg;
	int nro_jugador;
	int posicion_bala;
	int done;
	int i;
	char mensaje_enviar[5];

	done=0;

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	posicion_bala = generar_numero_random(0,6);
	printf("La bala esta en el numero %d \n", posicion_bala);


	for (i=0; i<6; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_REVOLVER, EVT_INICIO, "");
	}

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_REVOLVER, &msg);
		printf("recibo mensaje\n");
		nro_jugador = msg.int_rte-MSG_JUGADOR;

		switch (msg.int_evento) {
			case EVT_INICIO:
				printf("iniciando..\n");
				break;
			case EVT_DISPARO:
				printf("El jugador %d se disparo con el tambor %d\n", nro_jugador, atoi(msg.char_mensaje));
				if (atoi(msg.char_mensaje) == posicion_bala) {
					sprintf(mensaje_enviar, "%d", posicion_bala);
					for (i=0; i<6; i++) {
						enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_REVOLVER, EVT_FIN, mensaje_enviar);
					}
					done=1;
				printf("Se murio el jugador %d\n", nro_jugador);
				} else {
					printf("Se salvo...\n");
					enviar_mensaje(id_cola_mensajes, msg.int_rte, MSG_REVOLVER, EVT_SALVADO, "");
				}
				break;
		}
	}

	return 0;
}
