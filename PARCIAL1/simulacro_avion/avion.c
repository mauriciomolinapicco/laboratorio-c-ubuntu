#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforos.h"

int main(int argc, char *argv[])
{
    Avion avion;
    int id_semaforo;
    FILE* archivo;
    char *ciudad;
    int opcion;

    if (argc < 2) {
        perror("Debe mandarse un parametro!\n");
        return 1;
    }

    if (atoi(argv[1]) < 1 || atoi(argv[1]) > 3){
        printf("Opción inválida. El parametro debe ser 1, 2 o 3.\n");
        return 1;
    }

    
    id_semaforo = creo_semaforo();

    avion.nro_avion = atoi(argv[1]);



    while (1) 
    {
        printf("Ingrese cualquier input para cargar un mensaje: \n");
        scanf("%d", &opcion);
        while (getchar() != '\n');



        espera_semaforo(id_semaforo);
        if (!leer_string(avion.ciudad, LARGO_CADENA, "Ingrese ciudad: ")) {
            printf("Error al leer la ciudad\n");
            continue;
        }

        archivo = abrir_archivo("aviones.txt","a");
        if (archivo != NULL) {
            escribir_archivo(archivo, &avion, sizeof(Avion), 1);
            cerrar_archivo(archivo);
        } else {
            perror("Error al abrir el archivo");
        }
       
        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*5);

    }

    return 0;
}
