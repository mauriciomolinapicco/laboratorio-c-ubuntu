#include "archivos.h"
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaramos el semáforo
int id_semaforo;

int main() {
    // Creamos el semáforo
    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE); // Inicialmente el semáforo está verde (el productor puede escribir)

    // Abrimos el archivo
    if (!abrirArchivo("archivo.txt", "a")) {
        exit(1);
    }

    char contenido[50];
    int contador = 1;

    while (contador <= VECES) {
        // Esperamos a que el semáforo esté verde para escribir
        espera_semaforo(id_semaforo);
        
        // Escribimos en el archivo
        sprintf(contenido, "Productor escribe número %d\n", contador);
        escribirArchivo(contenido);
        printf("Productor escribió: %s", contenido);

        // Levantamos el semáforo para permitir que el consumidor lea
        levanta_semaforo(id_semaforo);

        // Incrementamos el contador
        contador++;

        // Espera de 1 segundo para simular un proceso en el productor
        sleep(1);
    }

    // Cerramos el archivo
    cerrarArchivo();

    return 0;
}