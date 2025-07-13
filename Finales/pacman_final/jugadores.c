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
    int cant_jugadores=4;
    DatosJugador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;
    int id_semaforo;
    int id_memoria;
    int id_memoria_juego;
    int termino=0;
    int numeros_fantasmas[3];
    int fantasmas_muertos[3] = {0,0,0};
    int nro_pacman;
    
    Sincronizacion *memoria = NULL;  
	MemoriaJuego *memoria_juego = NULL;

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
			levanta_semaforo(id_semaforo);
            usleep(300 * 1000);
			break;
		} else{
			levanta_semaforo(id_semaforo);
			usleep(300 * 1000);
		}
	}

    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cant_jugadores);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	datos_thread = (DatosJugador*) malloc(sizeof(DatosJugador)*cant_jugadores);

    srand(time(NULL));

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for(i=0;i<3;i++) {
        numeros_fantasmas[i] = generar_numero_random(1,30);
    }

    nro_pacman = generar_numero_random(1,100);
    printf("**********NUMEROS****************\n");
    for(i=0; i<3; i++) {
        printf("Fantasma %d → %d\n", i+1, numeros_fantasmas[i]);
    }
    printf("Pacman: %d\n", nro_pacman);
    printf("**********FIN NUMEROS****************\n");

    for (i=0; i<cant_jugadores; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        datos_thread[i].termino = &termino;
        datos_thread[i].nro_pacman = nro_pacman;
        datos_thread[i].numeros_fantasmas = numeros_fantasmas;
        datos_thread[i].fantasmas_muertos = fantasmas_muertos;
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

