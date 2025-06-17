#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforos.h"

int main(int argc, char *argv[]) {
    Avion avion;
    int id_semaforo;
    FILE* archivo;
    int contador;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1) 
    {
        espera_semaforo(id_semaforo);

        archivo = abrir_archivo("aviones.txt","r");        
        system("clear");
        if (archivo != NULL) {
            printf("Lista de vuelos \n");
            contador = 0;
            while (leer_archivo(archivo, &avion, sizeof(Avion), 1) == 1) {
                printf("Numero de avion: %d | Ciudad: %s \n", avion.nro_avion, avion.ciudad);
                contador++;
            }
            if (contador > 5) {
                system("rm aviones.txt");
            } 
            cerrar_archivo(archivo);
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*5);

    }
}
