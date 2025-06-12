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
	char msg_enviar_cola[5];
	int id_memoria;
	int id_semaforo;
	int nro_via;
	int cant_vias;
	int cant_vehiculos;
	int cant_vehiculos_desencolar;
	int sleep_time;
    Sincronizacion *memoria = NULL;  

    if (argc < 3) {
        printf("Se debe mandar de parametro la cantidad de vias y de vehiculos \n");
        return 1;
    }

    cant_vias = atoi(argv[1]);
	cant_vehiculos = atoi(argv[2]);


    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	printf("Autos preparados\n");
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

	printf("---Se vienen %d autos --- \n\n", cant_vehiculos);

	while (done==0)
	{
		cant_vehiculos_desencolar = generar_numero_random(1,5);
		nro_via = generar_numero_random(0,cant_vias);
		cant_vehiculos -= cant_vehiculos_desencolar;
		if (cant_vehiculos < 0) {
			cant_vehiculos += cant_vehiculos_desencolar;
			cant_vehiculos_desencolar = cant_vehiculos;
			done = 1;
		}
		printf("Se mandan %d vehiculos a la via %d || Quedan %d \n", cant_vehiculos_desencolar, nro_via, cant_vehiculos);
		sprintf(msg_enviar_cola, "%d", cant_vehiculos_desencolar);
		enviar_mensaje(id_cola_mensajes, MSG_VIAS+nro_via, MSG_AUTOS, EVT_VEHICULOS, msg_enviar_cola);
		
		sleep_time = generar_numero_random(100,500);
		usleep(sleep_time*1000);
	}

	for (i=0;i<cant_vias;i++) {
		enviar_mensaje(id_cola_mensajes, MSG_VIAS+i, MSG_AUTOS, EVT_FINALIZAR, "");
	}

	liberar_memoria(id_memoria, (char *)memoria);
	printf("Fin del programa\n");	

	return 0;
}

