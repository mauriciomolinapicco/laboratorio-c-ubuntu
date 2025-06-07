#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "cola.h"
#include "def.h"

void finalizar_carrera(int id_cola) {
	int i;
	for (i=0;i<3;i++) {
		enviar_mensaje(id_cola, MSG_ANIMAL+i, MSG_CANCHA, EVT_FIN, "");
	} 
}

void mostrar_ganador(Animal animales[]) {
	int i;
	int cant_ganadores=0;
	char ganador[30];
	for (i=0;i<3;i++) {
		printf("%s dio %d pasos en %d veces \n", animales[i].nombre, animales[i].pasos, animales[i].veces);
		if (animales[i].pasos >= 117) {
			sprintf(ganador, "%s", animales[i].nombre);
			cant_ganadores++;
		}
	}
	if (cant_ganadores > 1) {
		printf("Empate\n");
	} else {
		printf("El ganador fue el %s", ganador);
	}
}

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    mensaje msg;
	int nro_animal;
	int done;
	int i;
	int pasos_corridos;
	char mensaje_enviar[5];
	Animal animales[3];
	int alguien_termino=0;

	done=0;

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	/*iniciando los threads*/
	for (i=0; i<6; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_ANIMAL+i, MSG_CANCHA, EVT_INICIO, "");
	}

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_CANCHA, &msg);
		nro_animal = msg.int_rte-MSG_ANIMAL;

		switch (msg.int_evento) {
			case EVT_INICIO:
				sprintf(animales[nro_animal].nombre, "%s", msg.char_mensaje);
				printf("El %s esta listo para empezar\n", animales[nro_animal].nombre);
				animales[nro_animal].pasos = 0;
				animales[nro_animal].veces = 0;
				break;
			case EVT_CORRO:
				pasos_corridos = atoi(msg.char_mensaje);
				animales[nro_animal].pasos += pasos_corridos;
				animales[nro_animal].veces++;
				enviar_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, MSG_CANCHA, EVT_CONTINUO, "");

				system("clear");
				printf("\t\t--Carrera--\n\n\n");

				/*mostrar datos*/
				for (i=0;i<3;i++) {
					printf("\t%s: Pasos: %d | Intentos: %d \n\n", animales[i].nombre, animales[i].pasos, animales[i].veces);
				}

				if (animales[nro_animal].pasos >= 117) {
					done=1;
					finalizar_carrera(id_cola_mensajes);
					mostrar_ganador(animales);
				}
				break;
			default:
				printf("Evento desconocido...\n");
				break;
		}
	}

	return 0;
}

