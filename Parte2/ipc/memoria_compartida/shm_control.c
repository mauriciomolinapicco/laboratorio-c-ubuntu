#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>

int main() {
    key_t key = ftok("archivo.txt", 65); // Generar una clave única
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Crear o acceder a la memoria compartida

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    struct shmid_ds shm_info;
    if (shmctl(shmid, IPC_STAT, &shm_info) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("Información sobre la memoria compartida:\n");
    printf("Tamaño: %zu bytes\n", shm_info.shm_segsz);
    printf("Número de procesos usando la memoria: %ld\n", shm_info.shm_nattch);
    printf("PID del creador: %d\n", shm_info.shm_cpid);
    printf("Última vez que se accedió: %s", ctime(&shm_info.shm_atime));

    return 0;
}
