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
    Jugada jugada;
    int id_semaforo;
    int cont_jugadas;
    int i;
    int lanzamiento;
    int bola_ingreso;
    FILE* archivo;

    id_semaforo = creo_semaforo();
    inicia_semaforo(id_semaforo, VERDE);
    
    if (argc < 2) {
        perror("Debe mandarse un parametro!\n");
        return 1;
    }

    if (atoi(argv[1]) < 1 || atoi(argv[1]) > 3){
        printf("Opción inválida. El parametro debe ser 1, 2 o 3.\n");
        return 1;
    }

    jugada.equipo = atoi(argv[1]);

    for(cont_jugadas=1;cont_jugadas<7;cont_jugadas++) {
        espera_semaforo(id_semaforo);
        jugada.turno = cont_jugadas;
        jugada.metros_recorridos = 0;
        for(i=0; i<3; i++)
        {
            jugada.metros[i] = generar_numero_random(10,35);
            jugada.metros_recorridos += jugada.metros[i];
        }

        if (jugada.metros_recorridos >= 70) {
            jugada.puntos = 7;
            jugada.bola_ingreso = generar_numero_random(1,2);
            if (jugada.bola_ingreso == 2) {
                jugada.puntos += 3;
            }
        } else {
            jugada.bola_ingreso = 1;
            jugada.puntos = 0;
        }

        printf("Equipo %d turno %d: %d %d %d, extra %d ----> %d puntos\n\n",
                jugada.equipo, jugada.turno, jugada.metros[0], jugada.metros[1], jugada.metros[2],
                jugada.bola_ingreso, jugada.puntos);

        archivo = abrir_archivo("jugadas.txt", "a");
        if (archivo != NULL) {
            escribir_archivo(archivo, &jugada, sizeof(Jugada), 1);
            cerrar_archivo(archivo);
        }

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*30);
    }
}
