#include "memoria.h"
#include <stdio.h>   
#include <stdlib.h>  
#include <errno.h>   
#include <string.h>  
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include "clave.h"


void* creo_memoria(int size, int* r_id_memoria, int clave_base)
{
    void* ptr_memoria;
    int id_memoria;

    id_memoria = shmget(creo_clave(clave_base), size, 0777 | IPC_CREAT);

    if (id_memoria == -1)
    {
        printf("No consigo id para memoria compartida\n");
        exit(0);
    }

    ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);

    if (ptr_memoria == NULL)
    {
        printf("No consigo memoria compartida\n");
        exit(0);
    }

    *r_id_memoria = id_memoria;
    return ptr_memoria;
}

void liberar_memoria(int id_memoria, char *memoria){
    shmdt(memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
}

