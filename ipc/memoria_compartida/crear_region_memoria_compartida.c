#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int main() {
    key_t key = ftok("archivo.txt", 65); // Generar una clave única
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Crear o acceder a la memoria compartida

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    printf("Memoria compartida creada con éxito, identificador: %d\n", shmid);

    return 0;
}
