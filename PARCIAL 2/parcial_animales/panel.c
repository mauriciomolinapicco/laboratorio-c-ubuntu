#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "def.h"
#include "global.h"
#include "mensajes.h"
#include "memoria.h"
#include "funciones.h"
#include "semaforo.h"


void voMostrarResultado(animal animales[]){
	int i;
	for(i=0; i<CANTIDAD; i++){
		printf("%s\n", animales[i].nombre);
		printf("Cantidad de veces que dio pasos: %d\n", animales[i].cant_veces_pasos);
		printf("Total de pasos: %d\n", animales[i].cant_pasos);
		puts(" ");
	}
}

void voImprimirGanador(animal animales[]){
	int ganador = 0;
	int ganadores = 0;
	int i;
	for(i=0; i<CANTIDAD; i++){
		if(animales[i].cant_pasos >= META){
			ganadores += 1;
			ganador = i;
		}
	}
	if(ganadores > 1){
		printf("\nEMPATE!\n");
	} else{
		printf("\nEl ganador es %s!\n", animales[ganador].nombre);
	}
}

int main(int argc, char *argv[])
{
	/*DECLARACION DE VARIABLES*/
	int id_cola_mensajes;
	int nro_animal;
	int done = 0;
	int id_semaforo;
	int id_memoria;
	animal animales[CANTIDAD];
	int animales_restantes;
	int max_cant_veces = 1000;
	int *listo = NULL;
	int pasos;
	int i;
	/*int ganador = 0;
	int ganadores = 0;*/
	mensaje msg;

	/*INICIO DEL CUERPO DEL PROGRAMA*/
	srand(time(NULL));
	listo = (int *)creo_memoria(sizeof(int), &id_memoria);
	*listo = 0;

	id_cola_mensajes = creo_id_cola_mensajes();

	borrar_mensajes(id_cola_mensajes); /*Borra todos los mensajes que haya en la cola.*/

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	
	/*me aseguro de que el programa no corra hasta que el otro este listo*/
	espera_semaforo(id_semaforo);
	(*listo)++;
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);

	while(TRUE){
		espera_semaforo(id_semaforo);
		if(*listo == 2){
			levanta_semaforo(id_semaforo);
			break;
		} else{
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
		}
	}

	/*inicializo la estructura animales */
	for(i=0; i<CANTIDAD; i++){
		memset(animales[i].nombre, 0x00, sizeof(animales[i].nombre));
		animales[i].cant_veces_pasos = 0;
		animales[i].cant_pasos = 0;
	}
	sprintf(animales[0].nombre, "%s", "Conejo");
	sprintf(animales[1].nombre, "%s", "Gato");
	sprintf(animales[2].nombre, "%s", "Perro");
	
	/*envio el mensaje inicio a todos los animales*/
	for(i=0; i<CANTIDAD; i++){
		enviar_mensaje(id_cola_mensajes, MSG_ANIMAL+i, MSG_PANEL, EVT_INIT, "INICIO");
	}

	animales_restantes = CANTIDAD;

	while(done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		/*Obtengo el id del jugador que me esta enviando el mensaje.*/
		nro_animal = msg.int_rte-MSG_ANIMAL;

		switch(msg.int_evento){
			case EVT_AVANZO:
				pasos = atoi(msg.char_mensaje);
				/*me aseguro de que si un animal da pasos extra no sean contados*/
				if(animales[nro_animal].cant_veces_pasos < max_cant_veces){
					animales[nro_animal].cant_pasos += pasos;
					animales[nro_animal].cant_veces_pasos += 1;
				}
				/*valido que se haya superado la meta o se haya dado la misma cantidad de vueltas que el primer animal que llego*/
				if(animales[nro_animal].cant_pasos >= META || animales[nro_animal].cant_veces_pasos == max_cant_veces){
					animales_restantes -= 1;
					if(max_cant_veces == 1000){
						max_cant_veces = animales[nro_animal].cant_veces_pasos;
					}
					if(animales_restantes == 0){
						done = 1;
					}
					enviar_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, MSG_PANEL, EVT_FIN, "FINALIZAR");
				} else{
					enviar_mensaje(id_cola_mensajes, MSG_ANIMAL+nro_animal, MSG_PANEL, EVT_CONTINUAR, "CONTINUAR");
				}

				/*borro pantalla y imprimo resultados*/
				system("clear");
				voMostrarResultado(animales);
			break;
			default:
				printf("Evento Desconocido\n");
			break;
		}
		usleep(ESPERA * 1000);
	};
	/*valido cuantos animales superaron la meta si es uno lo muestro y si fue mas de 1 es empate*/
	voImprimirGanador(animales);
	return 0;
}
