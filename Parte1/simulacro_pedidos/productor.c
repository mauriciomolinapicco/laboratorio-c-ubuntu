#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforos.h"

int main(int argc, char *argv[]) {
    Pedido pedido;
    FILE *archivo;
    int id_semaforo;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    
    printf("INICIANDO PRODUCTOR \n");
    while (1) {
        generar_pedido(&pedido);
        espera_semaforo(id_semaforo);
        archivo = abrir_archivo("menu.txt","a");
        if (archivo != NULL) {
            escribir_archivo(archivo, &pedido, sizeof(Pedido), 1);
            cerrar_archivo(archivo);
        } else {
            perror("Error al abrir el archivo");
        }
        levanta_semaforo(id_semaforo);
        sleep(1);
    }
    return 0;
}
