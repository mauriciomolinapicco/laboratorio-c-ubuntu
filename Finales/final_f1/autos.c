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
    DatosJugador *datos_thread;
    pthread_t* idHilo;
    pthread_attr_t 	atributos;
    int id_semaforo;
    int id_memoria;
    int id_memoria_autos;
    int termino=0;
    int pierde_turno;
    char modelos[4][20];
    int dado;
    
    Sincronizacion *memoria = NULL;  
	MemoriaAutos *memoria_autos = NULL;
    datos_thread = (DatosJugador*) malloc(sizeof(DatosJugador)*CANTIDAD_AUTOS);

    srand(time(NULL));

    strcpy(modelos[0], "Ferrari");
    strcpy(modelos[1], "McLaren");
    strcpy(modelos[2], "BMW");
    strcpy(modelos[3], "Fiat");
    
    memoria = (Sincronizacion*)creo_memoria(sizeof(Sincronizacion), &id_memoria, CLAVE_BASE);    
    memoria_autos = (MemoriaAutos*)creo_memoria(sizeof(MemoriaAutos), &id_memoria_autos, CLAVE_BASE_2);

	id_semaforo = creo_semaforo();

	espera_semaforo(id_semaforo);
    for (i=0;i<CANTIDAD_AUTOS;i++) {
        /*pais*/
        printf("Ingrese el nombre del pais del auto %d: ", i);
        leer_cadena(memoria_autos->autos[i].pais);
        strcpy(datos_thread[i].pais, memoria_autos->autos[i].pais);

        /*modelo*/
        dado = generar_numero_random(0,3);
        strcpy(memoria_autos->autos[i].modelo, modelos[dado]);
        strcpy(datos_thread[i].modelo, modelos[dado]);

        printf("El auto sera un %s \n", modelos[dado]);
        if (dado < 2) {
            memoria_autos->autos[i].es_mclaren_o_ferrari = 1;
            datos_thread[i].es_mclaren_o_ferrari = 1;
        } else {
            memoria_autos->autos[i].es_mclaren_o_ferrari = 0;
            datos_thread[i].es_mclaren_o_ferrari = 0;
        }

        memoria_autos->autos[i].metros_recorridos=0;
    }
	memoria->proceso_2_preparado=1;
    
    printf("autos preparados\n");
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


    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*CANTIDAD_AUTOS);
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

    for (i=0; i<CANTIDAD_AUTOS; i++)
    {
        datos_thread[i].nro_jugador = i;
        datos_thread[i].id_cola_mensaje = id_cola_mensajes;
        datos_thread[i].termino = &termino;
        pthread_create(&idHilo[i], &atributos, ThreadJugador, &datos_thread[i]);
    }


  	for(i=0;i<CANTIDAD_AUTOS;i++)
	{
		pthread_join (idHilo[i], NULL);
		printf("Finalizo jugador %d \n", i);
	}

    if (termino == 0) {
        printf("Chocaron todos! Empate... \n");
        enviar_mensaje(id_cola_mensajes, MSG_PANEL, MSG_JUGADOR+0, EVT_EMPATE, "");
    }

    free(idHilo);
    free(datos_thread);
    liberar_memoria(id_memoria, (char *)memoria);
    liberar_memoria(id_memoria_autos, (char *)memoria_autos);

    return 0;
}

