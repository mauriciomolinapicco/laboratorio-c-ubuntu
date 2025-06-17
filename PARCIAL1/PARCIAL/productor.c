#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "archivos.h"
#include "def.h"
#include "semaforos.h"

#define INTERVALO 1000000
#define PRECIO_MT2 2000
#define MAX_PROPIEDADES 4

typedef struct {
    int id;
    char nombre[50];
    int metros_cuadrados;
    float valor;
} Propiedad;

void carga_propiedad(Propiedad *propiedad) {
    // Genera un ID aleatorio entre 1 y 9999
    propiedad->id = rand() % 9999 + 1;

    // Genera un nombre aleatorio para la propiedad
    sprintf(propiedad->nombre, "Propiedad-%d", propiedad->id);

    // Genera metros cuadrados aleatorios entre 20 y 100
    propiedad->metros_cuadrados = rand() % 81 + 20;

    // Calcula el valor de la propiedad en base al precio por metro cuadrado
    propiedad->valor = propiedad->metros_cuadrados * PRECIO_MT2;
}

int main() {
    srand(time(NULL)); // Inicializa la semilla para números aleatorios
    int id_semaforo;
    Propiedad propiedad;
    FILE *archivo;
    int num_propiedades = 0;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    printf("Iniciando AlquiCor - Gestión de Propiedades\n");

    while (1) {
        espera_semaforo(id_semaforo);

        if (num_propiedades < MAX_PROPIEDADES) {
            printf("\n--- Carga de Nueva Propiedad ---\n");
            carga_propiedad(&propiedad);

            archivo = abrir_archivo("propiedades.txt", "a");
            if (archivo != NULL) {
                escribir_archivo(archivo, &propiedad, sizeof(Propiedad), 1);
                cerrar_archivo(archivo);
                num_propiedades++;
            } else {
                perror("Error al abrir el archivo");
            }

            printf("Propiedad cargada -> ID: %d, Nombre: %s, Metros Cuadrados: %d, Valor: %.2f\n",
                   propiedad.id, propiedad.nombre, propiedad.metros_cuadrados, propiedad.valor);
        } else {
            printf("No se pueden cargar más propiedades. Limite alcanzado (%d)\n", MAX_PROPIEDADES);
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO * 10);
    }

    return 0;
}
