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
    int nro_via;
    int id_cola_mensajes;
    mensaje msg;
    int vehiculos_recibidos;
    int vehiculos_sacar_cola;
    int cant_vehiculos_en_cola=0;
    int done=0;
    DatosJugador *datos = (DatosJugador*) parametro;

    nro_via = datos->nro_via;
    id_cola_mensajes = datos->id_cola_mensaje;

    
    
    while (done==0) {
        recibir_mensaje(id_cola_mensajes, MSG_VIAS+nro_via, &msg);
        pthread_mutex_lock(&mutex);

        switch (msg.int_evento)
        {
        case EVT_VEHICULOS:
            vehiculos_recibidos = atoi(msg.char_mensaje);
            cant_vehiculos_en_cola += vehiculos_recibidos;
            datos->liberaciones_via += vehiculos_recibidos; /*contador para cuando salga del thread*/

            vehiculos_sacar_cola = generar_numero_random(1,10);
            cant_vehiculos_en_cola -= vehiculos_sacar_cola;

            if(cant_vehiculos_en_cola < 0) {
                /*verifico que no quede negativo*/
                cant_vehiculos_en_cola=0;
            }

            if(cant_vehiculos_en_cola > 10) {
                printf("Via: %d -> tengo mas de 10, liberando...", nro_via);
                cant_vehiculos_en_cola=0;
            }
            printf("Via %d | Recibi %d autos | Saque %d | Total restante: %d \n", nro_via, vehiculos_recibidos, vehiculos_sacar_cola, cant_vehiculos_en_cola);
            break;

        case EVT_FINALIZAR:
            printf("Via %d finalizando...\n", nro_via);
            done=1;
            break;
        
        default:
            printf("evento desconocido\n");
            break;
        }

        pthread_mutex_unlock(&mutex);
        usleep(300*1000);

    }
    
    
    pthread_exit ((void *)"Listo");

}

