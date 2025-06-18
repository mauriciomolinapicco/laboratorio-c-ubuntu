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
	int cantidad_productos;
	int done=0;
	int i;
	int opcion;
	int id_memoria;
	int id_semaforo;
	int numero_caja;
    char msg_a_cola[5];

	Producto *productos = NULL;

	productos = (Producto *)creo_memoria(sizeof(Producto), &id_memoria, CLAVE_BASE);
	

	/* VER
	Jugador jugadores[5]; */

	srand(time(NULL));

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

	while (!done)
    {
        printf("\n--- Menú Principal ---\n");
        printf("1. Agregar un producto\n");
        printf("2. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:

				printf("Ingrese el precio: ");
				scanf("%d", &productos[i].precio);

				while (getchar() != '\n');

				printf("Ingrese la descripción: ");
				leer_cadena(productos[i].descripcion);
				
				cantidad_productos = generar_numero_random(1,20);
				printf("Se compraran %d productos. Comenzando... \n");

				if (cantidad_productos >= 1 && cantidad_productos <= 5) {
					numero_caja = 0;
				} else if (cantidad_productos <= 10) {
					numero_caja = 1;
				} else {
					numero_caja = 2;
				}
				sprintf(msg_a_cola, "%d", cantidad_productos);
				enviar_mensaje(id_cola_mensajes, MSG_CAJA+numero_caja, MSG_SUPER, EVT_COMPRA, msg_a_cola);
                break;
            case 2:
                done = 1;
                break;
            default:
                printf("Opción no válida. Por favor, ingrese 1 o 2.\n");
                break;
        }
    }

	/*liberar memoria compartida*/
	liberar_memoria(id_memoria, (char *)productos);

	return 0;
}


