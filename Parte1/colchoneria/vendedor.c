#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "def.h"
#include "funciones.h"
#include "semaforos.h"
#include "clave.h"


int main(int argc, char *argv[]) {
    int id_semaforo;
    int id_memoria;
    Descripcion *memoria = NULL;

    memoria = (Descripcion*)creo_memoria(sizeof(Descripcion)*10, &id_memoria, CLAVE_BASE);


    while(1) {
        espera_semaforo(id_semaforo);

        levanta_semaforo(id_semaforo);
        usleep(INTERVALO*20);
    }
    
    shmdt ((char *)memoria);
    shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
