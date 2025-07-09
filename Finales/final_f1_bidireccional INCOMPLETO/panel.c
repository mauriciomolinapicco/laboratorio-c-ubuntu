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
	int id_memoria_autos;
	int id_semaforo;
	int cant_autos=10;
	int contador=0;
	int termino_flag=0;
	Auto autos[10];

    Sincronizacion *memoria = NULL;  
	MemoriaAutos *memoria_autos = NULL;

	memoria_autos = (MemoriaAutos*)creo_memoria(sizeof(MemoriaAutos), &id_memoria_autos, CLAVE_BASE_2);    

	memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    

	id_semaforo = creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	espera_semaforo(id_semaforo);
	memoria->proceso_1_preparado=1;
	printf("Panel preparado! \n");
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);

	while(1){
		espera_semaforo(id_semaforo);
		if(memoria->proceso_2_preparado==1){
			for (i = 0; i < cant_autos; i++) {
				strcpy(autos[i].pais, memoria_autos->autos[i].pais);
				strcpy(autos[i].modelo, memoria_autos->autos[i].modelo);
				autos[i].es_mclaren_o_ferrari = memoria_autos->autos[i].es_mclaren_o_ferrari;
				printf("Auto %d - País: %s | Modelo: %s | Es Ferrari o McLaren: %d\n",
					i,
					autos[i].pais,
					autos[i].modelo,
					autos[i].es_mclaren_o_ferrari
				);
				autos[i].metros_recorridos = memoria_autos->autos[i].metros_recorridos;
			}

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
	
	/* inicio o despierto a los autos*/
	for (i=0; i<CANTIDAD_AUTOS; i++) {
		enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_PANEL, EVT_AVANZO, "");
		autos[i].metros_recorridos=0;
	}

	while (done==0)
	{
		recibir_mensaje(id_cola_mensajes, MSG_PANEL, &msg);
		nro_jugador = msg.int_rte - MSG_JUGADOR;

		mensaje_recibido = atoi(msg.char_mensaje);
		autos[nro_jugador].metros_recorridos += mensaje_recibido;

	    switch (msg.int_evento) {
			case EVT_AVANZO:
				printf("Auto %d: [%s:%s] avanzo %d metros | Total: %d \n",nro_jugador, autos[nro_jugador].pais, autos[nro_jugador].modelo, mensaje_recibido, autos[nro_jugador].metros_recorridos);
				contador++;
				break;

			case EVT_CHOCO:
				printf("Auto %d: [%s:%s] CHOCO! FUERA DE CARRERA \n",nro_jugador, autos[nro_jugador].pais, autos[nro_jugador].modelo);
				autos[nro_jugador].choco = 1;
				break;

			case EVT_BOXES:
				printf("Auto %d: [%s:%s] Entra a boxes y no avanzara esta ronda... \n",nro_jugador, autos[nro_jugador].pais, autos[nro_jugador].modelo);
				autos[nro_jugador].choco = 1;
				break;

			default:
				printf("Evento desconocido \n");
				break;
		
    	}

		if(autos[nro_jugador].metros_recorridos >= TOTAL_METROS) {
			termino_flag = 1;
		}

		if (contador >= CANTIDAD_AUTOS) {
			if (termino_flag == 1) {
				/* la carrera termino */
				for (i=0;i<CANTIDAD_AUTOS;i++) {
					/* aca deberia controlar el maximo de metros que se realizaron */
					
				}
			}


			contador = 0;
			for (i=0;i<CANTIDAD_AUTOS;i++) {
				if (autos[i].choco == 0) {
					enviar_mensaje(id_cola_mensajes, MSG_JUGADOR+i, MSG_PANEL, EVT_AVANZO, "");
				}
			}
		}

		usleep(200*1000);
	}

	liberar_memoria(id_memoria, (char *)memoria);
	liberar_memoria(id_memoria_autos, (char *)memoria_autos);

	printf("Fin del programa\n");

	return 0;
}

