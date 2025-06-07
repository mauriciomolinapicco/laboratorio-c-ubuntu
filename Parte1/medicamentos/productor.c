#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforo.h"

int main(int argc, char *argv[]) {
    Medicamento med;
    FILE *archivo;
    int id_semaforo;


    /** Crear e iniciar semaforo */
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE); /* Inicia en 1 (VERDE) */

    printf("Productor iniciado\n");
    while(1){
        generar_medicamento(&med);
        mostrar_medicamento(&med); /* Opcional */
 
        /* ESpero lectura y luego escribo en el archivo con semaforo */
        espera_semaforo(id_semaforo);
        archivo = abrir_archivo("medicamentos.txt", "a");
        if (archivo != NULL) {
            escribir_archivo(archivo, &med, sizeof(Medicamento), 1);
            cerrar_archivo(archivo);
        } else {
            perror("Error al abrir archivo para escritura");
        }
        levanta_semaforo(id_semaforo);

        sleep(1); /* Simular tiempo de produccion */
    }

 
    return 0;
}
