#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "def.h"
#include "funciones.h"
#include "semaforos.h"
#include "clave.h"


int main(int argc, char *argv[]) {
    int id_semaforo;
    int id_memoria;
    Descripcion *memoria = NULL;
    int i;

    memoria = (Descripcion*)creo_memoria(sizeof(Descripcion)*10, &id_memoria, CLAVE_BASE);
    inicia_semaforo(id_semaforo, VERDE);

    for(i=0;i<5;i++) {
        memoria[i].codigo = i+1;
        memoria[i].cantidad = 10;
    }

    strcpy(memoria[0].nombre, "PIERO");
    strcpy(memoria[1].nombre, "SUAVESTAR");
    strcpy(memoria[2].nombre, "CANNON");
    strcpy(memoria[3].nombre, "SIMMONS");
    strcpy(memoria[4].nombre, "BELMO");

    while(1) {
        espera_semaforo(id_semaforo);
        
        for(i=0;i<5;i++) {
            printf("%d %d %s",memoria[i].codigo, memoria[i].cantidad, memoria[i].nombre);
            if(memoria[i].cantidad < 10) {
                printf("Le sumo 1 colchon a %d", memoria[i].codigo);
                memoria[i].cantidad += 1;
            }
        }
        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*20);
    }
    
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}