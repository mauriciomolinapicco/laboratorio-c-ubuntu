#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "archivos.h"
#include "def.h"
#include "semaforos.h"

int main(int argc, char *argv[]) {
    char sistema;
    int id_semaforo;
    Pedido pedido;
    FILE* archivo;
    
    int cant_pedidos;
    int total_ventas;

    if (argc < 2) {
        perror("Debe mandarse un parametro!\n");
    }

    if (toupper(argv[1][0]) == 'A' || toupper(argv[1][0]) == 'B' || toupper(argv[1][0]) == 'C') {
        printf("Opción válida: %c\n", argv[1][0]);
    } else {
        printf("Opción inválida. Ingrese A, B o C.\n");
        return 1;
    }

    sistema = argv[1][0];
    id_semaforo = creo_semaforo();

    /* inicia_semaforo(id_semaforo, ROJO); */

    while(1) {
        cant_pedidos=0;
        total_ventas=0;
        espera_semaforo(id_semaforo);
        archivo = abrir_archivo("menu.txt","r");
        if (archivo != NULL) {
            while (leer_archivo(archivo, &pedido, sizeof(Pedido), 1) == 1) {
                if (pedido.menu == sistema) {
                    cant_pedidos++;
                    if (pedido.incluye_postre == 1) {
                        pedido.precio = pedido.precio + 200;
                    }
                    total_ventas = total_ventas + pedido.precio;
                }
            }
            cerrar_archivo(archivo);
        }
        levanta_semaforo(id_semaforo);

        system("clear"); /*limpia consola*/
        printf("\n ----- Sistema %c ----- \n", sistema);
        printf("Cantidad de pedidos: %d\n", cant_pedidos);
        printf("Total en dinero: $%d\n", total_ventas);
        usleep(INTERVALO);
        
    }

    return 0; /*nunca va a llegar aca */
}
