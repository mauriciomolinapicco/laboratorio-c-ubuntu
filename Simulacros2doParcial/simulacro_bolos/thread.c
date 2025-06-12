#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "def.h"
#include "thread.h"
#include "global.h"
#include "funciones.h"
#include "cola.h"

void *ThreadJugador (void *parametro)
{
    int nro_jugador;
    int id_cola_mensajes;
    int cant_jugadores;
    mensaje msg;
    int cant_pinos_derrubados;
    DatosJugador *datos = (DatosJugador*) parametro;
    int intentos=0;

    nro_jugador = datos->nro_jugador;
    id_cola_mensajes = datos->id_cola_mensaje;

    
    recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
    
    while (msg.int_evento != EVT_FIN) {
        
        
        pthread_mutex_lock(&mutex);
        enviar_mensaje(id_cola_mensajes, MSG_BOLERA, MSG_JUGADOR+nro_jugador, EVT_TIRO, "");

        recibir_mensaje(id_cola_mensajes, MSG_JUGADOR+nro_jugador, &msg);
        cant_pinos_derrubados = atoi(msg.char_mensaje);
        datos->cant_puntos += cant_pinos_derrubados;
        intentos++;

        switch (msg.int_evento)
        {
        case EVT_RESULTADO:
            printf("Jugador %d | Derrubo %d pinos | Intentos: %d !\n", nro_jugador, cant_pinos_derrubados,intentos);
            break;

        case EVT_FIN:
            if(cant_pinos_derrubados == 20) {
                printf("Jugador %d: CHUZA!", nro_jugador);
                break;
            }
            printf("TERMINO JUGADOR %d => Puntos: %d!\n", nro_jugador, cant_pinos_derrubados);
            break;
        
        default:
            printf("evento desconocido\n");
            break;
        }

        pthread_mutex_unlock(&mutex);
        usleep(500*1000);


        
    }
    
    
    pthread_exit ((void *)"Listo");

}

