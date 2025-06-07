#include "def.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* archivo;
    Medicamento medicamento;
    int id_semaforo;

    int total_medicamentos;
    int total_pastillas;

    int total_rojo;
    int total_amarillo;
    int total_fucsia;
    int total_pastillas_rojo;
    int total_pastillas_amarillo;
    int total_pastillas_fucsia;

    char sistema;

    if (argc < 2) {
        perror("Se debe enviar un argumento!\n");
    }

    if (toupper(argv[1][0]) == 'A' || toupper(argv[1][0]) == 'B' || toupper(argv[1][0]) == 'C') {
        printf("Opción válida: %c\n", argv[1][0]);
    } else {
        printf("Opción inválida. Ingrese A, B o C.\n");
        return 1;
    }

    sistema = argv[1][0]; 


    id_semaforo = creo_semaforo();

    while(1) {
        total_medicamentos = 0;
        total_pastillas = 0;
        total_rojo = 0;
        total_amarillo = 0;
        total_fucsia = 0;
        total_pastillas_rojo = 0;
        total_pastillas_amarillo = 0;
        total_pastillas_fucsia = 0;

        espera_semaforo(id_semaforo);
        archivo = abrir_archivo(FILE_NAME,"r");
        while (leer_archivo(archivo, &medicamento, sizeof(Medicamento), 1) == 1) {
            if (medicamento.sistema == sistema) {
                total_medicamentos++;
                total_pastillas += medicamento.cantidad;
                switch (medicamento.color) {
                    case 1:
                        total_rojo++;
                        total_pastillas_rojo += medicamento.cantidad;
                        break;
                    case 2:
                        total_amarillo++;
                        total_pastillas_amarillo += medicamento.cantidad;
                        break;
                    case 3:
                        total_fucsia++;
                        total_pastillas_fucsia += medicamento.cantidad;
                        break;
                }
            } 
        }
        levanta_semaforo(id_semaforo);
        system("clear");
        printf("\n--- Sistema %c --- \n", sistema);
        printf("Cantidad de medicamentos: %d | Cantidad de pastillas: %d\n", total_medicamentos, total_pastillas);
        printf("Rojo -> cant medicamentos: %d | cant pastillas: %d\n", total_rojo, total_pastillas_rojo);
        printf("Amarillo -> cant medicamentos: %d | cant pastillas: %d\n", total_amarillo, total_pastillas_amarillo);
        printf("Fucsia -> cant medicamentos: %d | cant pastillas: %d\n", total_fucsia, total_pastillas_fucsia);

        usleep(INTERVALO); /*100ms*/
    }

    

}
