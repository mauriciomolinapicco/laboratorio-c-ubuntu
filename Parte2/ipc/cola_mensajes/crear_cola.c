#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {
    key_t key = ftok("archivo.txt", 65);  // Generar la clave con ftok()
    
    // Crear o acceder a la cola de mensajes con permisos 0666
    int msqid = msgget(key, IPC_CREAT | 0666);
    
    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    printf("Cola de mensajes creada o accesada con éxito. msqid = %d\n", msqid);
    return 0;
}
