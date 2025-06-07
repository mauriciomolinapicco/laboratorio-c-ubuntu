#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main() {
    key_t key = ftok("archivo.txt", 65); // Generar una clave única
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Crear la memoria compartida

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Asociar la memoria compartida al espacio de direcciones del proceso
    char *shmaddr = (char*) shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Escribir en la memoria compartida
    printf("Escribe algo en la memoria compartida: ");
    fgets(shmaddr, 1024, stdin);

    printf("Se ha escrito en la memoria compartida: %s\n", shmaddr);

    // Desasociar la memoria compartida
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
