#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {
    int msqid = msgget(1234, 0666);  // Acceder a la cola de mensajes con la clave 1234

    // Eliminar la cola de mensajes
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Cola de mensajes eliminada exitosamente.\n");
    return 0;
}
