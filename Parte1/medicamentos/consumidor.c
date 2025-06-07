#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforo.h"
#include "clave.h"

void procesar_sistema(char sistema, int id_semaforo);

int main(int argc, char *argv[]) {
    int id_semaforo;
    char sistema;

    /** Verificar argumento */
    if (argc != 2 || (argv[1][0] != 'A' && argv[1][0] != 'B' && argv[1][0] != 'C')) {
        printf("Uso: %s A|B|C\n", argv[0]);
        return 1;
    }

    sistema = argv[1][0];

    /** Obtener semaforo existente */
    id_semaforo = creo_semaforo();

    /** Procesar el sistema */
    procesar_sistema(sistema, id_semaforo);

    return 0; /* No llegara aqui porque procesar_sistema es infinito */
}
 

void procesar_sistema(char sistema, int id_semaforo) {
    Medicamento med;
    FILE *archivo;
    int total_pastillas = 0;
    int total_meds = 0;
    int colores[3] = {0, 0, 0};          /* Contadores para Rojo (1), Amarillo (2), Fucsia (3) */
    int pastillas_por_color[3] = {0, 0, 0}; /* Pastillas para Rojo, Amarillo, Fucsia */

    printf("Consumidor %c iniciado\n", sistema);
    while (1) {
        total_pastillas = 0;        
        total_meds = 0;             
        colores[0] = 0;             
        colores[1] = 0;             
        colores[2] = 0;             
        pastillas_por_color[0] = 0; 
        pastillas_por_color[1] = 0; 
        pastillas_por_color[2] = 0; 

        espera_semaforo(id_semaforo);
        archivo = abrir_archivo("medicamentos.txt", "r");
        if (archivo != NULL) {
            while (leer_archivo(archivo, &med, sizeof(Medicamento), 1) == 1) {
                if (med.sistema == sistema) {
                    total_meds++;
                    total_pastillas += med.cantidad;
                    colores[med.color - 1]++;             /* Contar medicamentos por color */
                    pastillas_por_color[med.color - 1] += med.cantidad; /* Sumar pastillas por color */
                    mostrar_medicamento(&med);
                }
            }
            cerrar_archivo(archivo);
        }
        levanta_semaforo(id_semaforo);
        system("clear"); /* Limpiar la consola */

        printf("Sistema %c - Total medicamentos: %d, Total pastillas: %d\n", 
               sistema, total_meds, total_pastillas);
        printf("Rojo: %d meds, %d pastillas\n", colores[0], pastillas_por_color[0]);
        printf("Amarillo: %d meds, %d pastillas\n", colores[1], pastillas_por_color[1]);
        printf("Fucsia: %d meds, %d pastillas\n", colores[2], pastillas_por_color[2]);
        usleep(INTERVALO); /* Chequear cada 100ms */
    }
}
