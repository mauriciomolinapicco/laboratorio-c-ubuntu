#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "archivos.h"
#include "def.h"
#include "semaforos.h"

int main(int argc, char *argv[])
{   
    FILE* archivo;
    Panel panel;
    char nombre_archivo[20];
    int id_semaforo;
    int nro_panel;
    char mensaje_actual[LARGO_MENSAJE] = "";

    if (argc < 2) {
        perror("Debe mandarse un parametro!\n");
        return 1;
    }
    if (strcmp(argv[1], "1") == 0 || strcmp(argv[1], "2") == 0 || strcmp(argv[1], "3") == 0) {
        printf("Opción válida: %s\n", argv[1]);
        nro_panel = atoi(argv[1]);
    } else {
        printf("Opción inválida. Ingrese 1,2 o 3.\n");
        return 1;
    }

    id_semaforo = creo_semaforo();
    sprintf(nombre_archivo, "panel%d.txt", nro_panel);

    strcpy(mensaje_actual, DEFAULT_MSG);
    printf("--- PANEL %d --- \n", nro_panel);
    printf("Mensaje del panel: %s\n", mensaje_actual);

    while(1) 
    {   
        espera_semaforo(id_semaforo);
        archivo = abrir_archivo(nombre_archivo, "r");
        if (archivo != NULL) {
            if (leer_archivo(archivo,&panel,sizeof(Panel),1) == 1) {
                if (strcmp(panel.mensaje, mensaje_actual) != 0) {
                    system("clear");
                    strcpy(mensaje_actual, panel.mensaje);

                    printf("--- PANEL %d --- \n", nro_panel);
                    printf("Nuevo mensaje del panel: %s\n", mensaje_actual);
                }   
            }
        }
        levanta_semaforo(id_semaforo);
        usleep(INTERVALO);
    }

    return 0;

}
