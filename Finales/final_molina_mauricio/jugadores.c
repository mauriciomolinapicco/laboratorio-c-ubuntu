#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "funciones.h"
#include "cola.h"
#include "def.h"
#include "thread.h"
#include "global.h"
#include "semaforos.h"
#include "memoria.h"


int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    int i;
    int cant_jugadores=CANTIDAD_JUGADORES;
    DatosJugador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;
    int id_semaforo;
    int id_memoria;
    int id_memoria_juego;
    int termino=0;
    int cantidad_peces_muertos=0;
    int total_metros;
    char nombres_jugadores[CANTIDAD_JUGADORES][20];
    int metros_avanzados[CANTIDAD_JUGADORES] = {0,0,0,0,0,0};
    int peces_muertos[3] = {0,0,0}; /* lo uso para controlar cuales peces fueron comidos*/
    
    Sincronizacion *memoria = NULL;  
	MemoriaJuego *memoria_juego = NULL;

    strcpy(nombres_jugadores[0], "Pez 1");
    strcpy(nombres_jugadores[1], "Pez 2");
    strcpy(nombres_jugadores[2], "Pez 3");
    strcpy(nombres_jugadores[3], "Tiburon");
    strcpy(nombres_jugadores[4], "Pulpo 1");
    strcpy(nombres_jugadores[5], "Pulpo 2");

    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    
    memoria_juego = (MemoriaJuego*)creo_memoria(sizeof(MemoriaJuego), &id_memoria_juego, CLAVE_BASE_2);    

	id_semaforo = creo_semaforo();

	espera_semaforo(id_semaforo);
	memoria->proceso_2_preparado=1;
    
    printf("jugadores preparados\n");
	levanta_semaforo(id_semaforo);
	usleep(300 * 1000);
	
	while(1){
		espera_semaforo(id_semaforo);
		if(memoria->proceso_1_preparado==1){
            total_metros = memoria_juego->total_metros;
			levanta_semaforo(id_semaforo);
            usleep(300 * 1000);
			break;
		} else{
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
		}
	}

    printf("Se leyo de memoria que se deben hacer %d metros \n", total_metros);

    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_jugadores);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (DatosJugador*) malloc(sizeof(DatosJugador)*cant_jugadores);

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for (i=0; i<cant_jugadores; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        datos_thread[i].total_metros = total_metros;
        datos_thread[i].termino = &termino;
        datos_thread[i].cantidad_peces_muertos= &cantidad_peces_muertos;
        datos_thread[i].metros_avanzados = metros_avanzados;
        datos_thread[i].peces_muertos = peces_muertos;
        strcpy(datos_thread[i].nombre_jugador, nombres_jugadores[i]);
        pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
    }

  	for(i=0;i<cant_jugadores;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo jugador %d \n", i);
	}

    free(idHilo);
    free(datos_thread);
    liberar_memoria(id_memoria, (char *)memoria);
    liberar_memoria(id_memoria_juego, (char *)memoria_juego);

    return 0;
}


