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
	int i;
	int voto;
	int id_memoria;
	int id_semaforo;
	Postulante presidentes[2];
	Postulante vices[2];
	int cant_votos_total=0;

    Sincronizacion *memoria = NULL;  


	memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);

	memoria->proceso_1_preparado=1;
	printf("Panel preparado\n");

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
	
	for (i=0; i<2; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_VOTANTE+i, MSG_PANEL, EVT_INICIO, "");
		presidentes[i].cant_votos=0;
		vices[i].cant_votos=0;
	}

	strcpy(presidentes[0].nombre, "Senior MS");
	strcpy(presidentes[1].nombre, "Senior MI");

	strcpy(vices[0].nombre, "Senior A");
	strcpy(vices[1].nombre, "Seniora V");

	while (cant_votos_total < CANT_VOTANTES*2)
	{
	
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);

		voto = atoi(msg.char_mensaje);
		cant_votos_total++;

	    switch (msg.int_evento) {
			case EVT_VOTO_PRESIDENTE:
				printf("Nuevo voto para PRESIDENTE: %s \n", presidentes[voto].nombre);
				presidentes[voto].cant_votos++;
				break;
			
			case EVT_VOTO_VICE:
				printf("Nuevo voto para VICE: %s \n", vices[voto].nombre);
				vices[voto].cant_votos++;
				break;				

			default:
				printf("Evento desconocido \n");
				break;
    	}

		usleep(100*1000);
	}

	printf("--- RESULTADOS --- \n");

	if (presidentes[0].cant_votos > presidentes[1].cant_votos) {
		printf("PRESIDENTE: Ganador %s con %d votos \n", presidentes[0].nombre, presidentes[0].cant_votos);
	} else if (presidentes[0].cant_votos < presidentes[1].cant_votos) {
		printf("PRESIDENTE: Ganador %s con %d votos \n",
			presidentes[1].nombre,
			presidentes[1].cant_votos);
	}
	else {
		printf("EMPATE entre %s y %s con %d votos\n",
			presidentes[0].nombre,
			presidentes[1].nombre,
			presidentes[0].cant_votos);
	}

	if (vices[0].cant_votos > vices[1].cant_votos) {
		printf("VICEPRESIDENTE: Ganador %s con %d votos \n", vices[0].nombre, vices[0].cant_votos);
	} else if (vices[0].cant_votos < vices[1].cant_votos) {
		printf("VICEPRESIDENTE: Ganador %s con %d votos \n", vices[1].nombre, vices[1].cant_votos);
	}
	else {
		printf("EMPATE entre %s y %s con %d votos\n",
			vices[0].nombre,
			vices[1].nombre,
			vices[0].cant_votos);
	}



	liberar_memoria(id_memoria, (char *)memoria);

	printf("Fin del programa\n");	

	return 0;
}

