#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "def.h"
#include "funciones.h"
#include "archivos.h"
#include "semaforos.h"

int main(int argc, char *argv[]) {
    Jugada jugada;
    int id_semaforo;
    FILE* archivo;
    int puntos_equipo_1;
    int puntos_equipo_2;
    int contador;
    int vueltas;
    char extra[3];

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);

    while (1) 
    {
        espera_semaforo(id_semaforo);
        puntos_equipo_1=0;
        puntos_equipo_2=0;

    
        archivo = abrir_archivo("jugadas.txt","r");  
        system("clear");
      
        if (archivo != NULL) {
            vueltas=0;
            printf("=== MARCADOR ====\n");
            while (leer_archivo(archivo, &jugada, sizeof(Jugada), 1) == 1) {
                if (jugada.bola_ingreso == 2) {
                    strcpy(extra, "Si");
                } else {
                    strcpy(extra, "No");
                }

                printf("Equipo %d | turno %d | %dm %dm %dm | Extra %s | Puntos %d\n",
                jugada.equipo, jugada.turno, jugada.metros[0], jugada.metros[1], jugada.metros[2], extra,jugada.puntos);
                vueltas++;

                if (jugada.equipo == 1) {
                    puntos_equipo_1 += jugada.puntos;
                } else {
                    puntos_equipo_2 += jugada.puntos;
                }
            }
            cerrar_archivo(archivo);
            if (vueltas >= 12) {
                break;
            }
        } 

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*5);
    }

    printf("========\n");
    printf("RESULTADO FINAL\n");
    printf("El equipo 1 termino con %d puntos\n", puntos_equipo_1);
    printf("El equipo 2 termino con %d puntos\n", puntos_equipo_2);
}
