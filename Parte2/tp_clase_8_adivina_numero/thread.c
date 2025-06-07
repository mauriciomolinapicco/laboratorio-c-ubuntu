#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "funciones.h"
#include "def.h"
#include "global.h"



typedef struct {
    int nro_jugador;
    int* puntero_alguien_acerto;
    int cantidad_intentos;
    int numero_pensado;
} DatosJugador;


void* ThreadJugadores(void* parametro) {
    int nro_jugador;
    int numero_pensado_jugador;
    int acerto = 0;
    DatosJugador *datos = (DatosJugador*) parametro;
    
    nro_jugador = datos->nro_jugador;

    while(!acerto) {
        pthread_mutex_lock(&mutex);
        if (*(datos->puntero_alguien_acerto) != 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        numero_pensado_jugador = generar_numero_random(1,99);
        datos->cantidad_intentos++;

        if (numero_pensado_jugador == datos->numero_pensado) {
            *(datos->puntero_alguien_acerto) = datos->nro_jugador;
            acerto=1;
        }

        printf("Jugador %d | Nro=%d | Intentos=%d \n", nro_jugador, numero_pensado_jugador, datos->cantidad_intentos);

        pthread_mutex_unlock (&mutex);
        usleep(TIEMPO*500);
    }


    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int i = 0;
    int cantidad_jugadores;
    int alguien_acerto=0;
    int numero_pensado;
    pthread_attr_t atributos;
    pthread_t* idHilo;
    DatosJugador *datos_jugadores;

    if (argc < 2) {
        fprintf(stderr, "Debe haber al menos: %s jugadores\n", argv[0]);
        return 1;
    }

    cantidad_jugadores = atoi(argv[1]);
    idHilo = (pthread_t* ) malloc(sizeof(pthread_t)*cantidad_jugadores);
    pthread_attr_init(&atributos);
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&mutex, NULL);

    numero_pensado = generar_numero_random(1,99);
    printf("El nro a adivinar es %d \n", numero_pensado);

    datos_jugadores = (DatosJugador* ) malloc(sizeof(DatosJugador) * cantidad_jugadores);

    for(i=0; i < cantidad_jugadores; i++)
    {
        datos_jugadores[i].nro_jugador = i;
        datos_jugadores[i].numero_pensado = numero_pensado;
        datos_jugadores[i].puntero_alguien_acerto = &alguien_acerto;
        datos_jugadores[i].cantidad_intentos = 0;
        pthread_create(&idHilo[i], &atributos, ThreadJugadores, &datos_jugadores[i]);
    }

    for (i = 0; i < cantidad_jugadores; i++) {
        pthread_join(idHilo[i], NULL);
        printf("Jugador %d | Intentos %d \n", datos_jugadores[i].nro_jugador, datos_jugadores[i].cantidad_intentos);
    }

    printf("---GANADOR---\n");
    printf("El ganador fue el jugador %d \n", *datos_jugadores[0].puntero_alguien_acerto);


    free(idHilo);
    free(datos_jugadores);
    pthread_mutex_destroy(&mutex);
    pthread_attr_destroy(&atributos);

    return 0; 

}

