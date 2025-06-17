#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "archivos.h"
#include "def.h"
#include "semaforos.h"

#define INTERVALO 1000000
#define MAX_RESERVAS 100

typedef struct {
    int id_propiedad;
    char apellido[50];
    int dni;
} Reserva;

void mostrar_propiedades() {
    FILE *archivo;
    Propiedad propiedad;

    archivo = abrir_archivo("propiedades.txt", "r");
    if (archivo != NULL) {
        printf("\n--- CONSULTA DE PROPIEDADES ---\n");
        while (leer_archivo(archivo, &propiedad, sizeof(Propiedad), 1) == 1) {
            printf("ID: %d | Nombre: %s | Valor: $%.2f | Metros Cuadrados: %d\n",
                   propiedad.id, propiedad.nombre, propiedad.valor, propiedad.metros_cuadrados);
        }
        cerrar_archivo(archivo);
    } else {
        perror("Error al abrir el archivo");
    }
}

void reservar_propiedad(int id_propiedad, char apellido[], int dni) {
    FILE *archivo;
    Reserva reserva;

    reserva.id_propiedad = id_propiedad;
    strcpy(reserva.apellido, apellido);
    reserva.dni = dni;

    archivo = abrir_archivo("reservas.dat", "a");
    if (archivo != NULL) {
        escribir_archivo(archivo, &reserva, sizeof(Reserva), 1);
        cerrar_archivo(archivo);
        printf("Reserva realizada para la propiedad con ID %d a nombre de %s (DNI: %d)\n",
               reserva.id_propiedad, reserva.apellido, reserva.dni);
    } else {
        perror("Error al abrir el archivo de reservas");
    }
}

int main() {
    int id_semaforo;
    int opcion;
    Reserva reserva;
    FILE *archivo;
    int num_reservas = 0;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    printf("Iniciando AlquiCor - Gestión de Reservas\n");

    while (1) {
        espera_semaforo(id_semaforo);

        mostrar_propiedades();

        printf("\n¿Desea reservar alguna propiedad? (1: Sí / 0: No): ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            printf("Ingrese el ID de la propiedad a reservar: ");
            scanf("%d", &reserva.id_propiedad);
            printf("Ingrese su apellido: ");
            scanf(" %[^\n]", reserva.apellido);
            printf("Ingrese su DNI: ");
            scanf("%d", &reserva.dni);

            reservar_propiedad(reserva.id_propiedad, reserva.apellido, reserva.dni);
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO * 10);
    }

    return 0;
}
