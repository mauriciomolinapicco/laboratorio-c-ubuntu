#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "semaforos.h"
#include "archivos.h"
#include "clave.h"
#include "funciones.h"
#include "def.h"


int main(int argc, char *argv[])
{
    int id_semaforo;
    int i=1;
    Panel panel;
    FILE* archivo;
    int opcion;
    char nombre_archivo[20];


    id_semaforo = creo_semaforo();

    printf("--- Creando archivos ---\n");
    inicia_semaforo(id_semaforo, VERDE);

    espera_semaforo(id_semaforo);
    for (i; i<4; i++) {
        sprintf(nombre_archivo, "panel%d.txt", i);
        panel.nro_panel = i;
        strcpy(panel.mensaje, DEFAULT_MSG);

        archivo = abrir_archivo(nombre_archivo, "w");
        if(archivo != NULL) {
            escribir_archivo(archivo,&panel,sizeof(Panel),1);
            printf("nro panel %d y mensaje: %s\n", panel.nro_panel, panel.mensaje);
        }
        cerrar_archivo(archivo);
    }
    printf("Escribiendo mensajes default\n");

    levanta_semaforo(id_semaforo);
    usleep(INTERVALO*10);

    while(1) {
        printf("Ingrese una opcion. 1 para leer un archivo o 2 para escribir: \n");
        scanf("%d", &opcion);

        espera_semaforo(id_semaforo);

        if (opcion == 1) {
            printf("Cual panel quiere leer?\n");
            scanf("%d", &opcion);
            if (opcion == 1 || opcion == 2 || opcion == 3) {
                sprintf(nombre_archivo, "panel%d.txt", opcion);
                archivo = abrir_archivo(nombre_archivo,"r");
                if (archivo != NULL) {
                    if (leer_archivo(archivo,&panel,sizeof(Panel),1) == 1) {
                        printf("El panel %d tiene actualmente el mensaje: %s \n", panel.nro_panel, panel.mensaje);
                    } else {
                        printf("No se pudo leer %s\n", nombre_archivo);
                    }
                } else {
                    printf("no se pudo abrir %s\n", nombre_archivo);
                }
                cerrar_archivo(archivo);
            }
        }
        else if (opcion == 2) {
            printf("Cual panel quiere escribir?\n");
            scanf("%d", &opcion);
            if (opcion == 1 || opcion == 2 || opcion == 3) {
                panel.nro_panel = opcion;

                printf("Ingrese el mensaje para el panel: ");
                scanf(" %[^\n]", panel.mensaje);
                sprintf(nombre_archivo, "panel%d.txt", opcion);
                archivo = abrir_archivo(nombre_archivo, "w");
                if (archivo != NULL) {
                    escribir_archivo(archivo, &panel, sizeof(Panel), 1);
                    cerrar_archivo(archivo);
                }
            } else {
                printf("Opcion invalida, intente nuevamente...\n");
                levanta_semaforo(id_semaforo);
                continue;
            }
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*10);
    }

    return 0;
   
}
