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
	int done;
	int i;
	int alguien_llego=0;
	char *animales[] = {"Conejo", "Gato", "Perro"};

	int nro_jugador;
	typedef struct {
		int nro_jugador;
		int pasos_corridos_vuelta;
		int pasos;
		int vueltas;
	} Animal;
	Animal jugadores[3];

	/*lo que hare con esta es mandar a los 3 a correr solamente depsues de verificar
	que los tres corrieron una vuelta y que ninguno llego a la meta, porque sino da problemas
	para verificar si termino la carrera*/
	int control_vueltas=0;

	done=0;

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);


	printf("En sus marcas...\n");
	
	for (i=0; i<3; i++) {
		/*les pido que corran por primera vez*/
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_CANCHA, EVT_CORRO, "");
	} 

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_CANCHA, &msg);
		nro_jugador = msg.int_rte-MSG_JUGADOR;

		switch (msg.int_evento) {
			case EVT_CORRO:
				control_vueltas++;
				pasos_corridos_vuelta = atoi(msg.char_mensaje);
				pasos[nro_jugador] += pasos_corridos_vuelta;
				vueltas[nro_jugador] += 1;
				/*printf("Jugador %d | Corrio %d pasos | Acumulado: %d | Vueltas: %d \n", nro_jugador, pasos_corridos_vuelta, pasos[nro_jugador], vueltas[nro_jugador]); */
				printf("%s | Corrio %d pasos | Acumulado: %d | Vueltas: %d \n", animales[nro_jugador], pasos_corridos_vuelta, pasos[nro_jugador], vueltas[nro_jugador]);

				/*chequear si termino la carerra*/
				for(i=0;i<3;i++) {
					if (pasos[i] >= 117) {
						alguien_llego = 1;
					}
				}

				if(control_vueltas==3) {
					control_vueltas=0;
					printf("---------\n");

					if (alguien_llego == 1) {
						printf(" --- FIN CARRERA --- \n");
						for(i=0;i<3;i++) {
							/* printf("Jugador %d | Pasos: %d | Vueltas: %d ", i, pasos[i], vueltas[i]);*/
							printf("%s | Pasos: %d | Vueltas: %d ", animales[i], pasos[i], vueltas[i]);
							if (pasos[i] > 117) {
								printf("-> Ganador \n");
							} else {
								printf("\n");
							}
							enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_CANCHA, EVT_FIN, "");
						}
						

						done=1;
						break;
					}

					for(i=0;i<3;i++) {
						enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_CANCHA, EVT_CORRO, ""); /*les pido que corran una vuelta mas*/
					}
				}


				
				break;

			default:
				printf("ERROR...\n");
				break;
		}
	}

	return 0;
}

