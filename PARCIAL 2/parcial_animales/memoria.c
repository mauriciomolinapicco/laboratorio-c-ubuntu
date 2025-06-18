#include "stdlib.h"
#include "sys/ipc.h"
#include "stdio.h"
#include "sys/shm.h"
#include "clave.h"
#include "memoria.h"
#include "def.h"
#include "string.h"
#include "errno.h"


void* creo_memoria(int size, int* r_id_memoria){
    void* ptr_memoria;
    int id_memoria;
    id_memoria = shmget(creo_clave(), size, 0777 | IPC_CREAT);
    if (id_memoria == -1){
        printf("No consigo id para memoria compartida. Error: %s\n", strerror(errno));
        exit(0);
        }
    ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);
    if (ptr_memoria == NULL){
        printf("No consigo memoria compartida. Error: %s\n", strerror(errno));
        exit(0);
        }
    *r_id_memoria = id_memoria;
    return ptr_memoria;
    }

void liberar_memoria(int id_memoria, char *memoria){
    /* libera el espacio de memoria compartida */
    shmdt(memoria);
    /* pone un flag al espacio de memoria compartida para destruirlo despues */
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
}
