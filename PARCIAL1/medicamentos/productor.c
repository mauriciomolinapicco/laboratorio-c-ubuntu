#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaforos.h"
#include "archivos.h"
#include "clave.h"
#include "funciones.h"
#include "def.h"

void creo_medicamento(Medicamento *medicamento) {
    int cantidad;
    medicamento->tipo = generar_numero_random(1,3);
    medicamento->color = generar_numero_random(1,3);

    while (1) {
        printf("Ingrese la cantidad de medicamentos a generar: \n");
        scanf("%d", &cantidad);

        if (cantidad==5 || cantidad==10 || cantidad==20) {
            medicamento->cantidad = cantidad;
            break;
        } 
        printf("Valor incorrecto, debe ser 5, 10 o 20 \n");
    }


    switch (medicamento->cantidad) {
        case 5:
            medicamento->sistema = 'A';
            break;
        case 10:
            medicamento->sistema = 'B';
            break;
        case 20:
            medicamento->sistema = 'C';
            break;
        default:
            printf("Invalido\n");
            return;
    } 
    return;
}


int main(int argc, char *argv[])
{
    int id_semaforo;
    Medicamento medicamento;
    FILE* archivo;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    printf("Iniciando productor \n");

    while(1) 
    {
        espera_semaforo(id_semaforo);
        printf("\n --- Creacion de medicamentos --- \n");
        creo_medicamento(&medicamento);

        archivo = abrir_archivo(FILE_NAME, "a");
        if (archivo != NULL) {
            escribir_archivo(archivo, &medicamento, sizeof(Medicamento), 1);
            cerrar_archivo(archivo);    
        } else {
            perror("Error al abrir el archivo");
        }

        levanta_semaforo(id_semaforo);
        printf("Medicamento creado -> tipo: %d, color: %d, cantidad: %d, sistema: %c", medicamento.tipo, medicamento.color, medicamento.cantidad, medicamento.sistema);
        printf("\n --- Medicamento creado --- \n");
        usleep(INTERVALO_PARTIDA*1000);
    }

    return 0;
}
