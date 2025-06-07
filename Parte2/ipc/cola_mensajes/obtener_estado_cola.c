#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {
    int msqid = msgget(1234, 0666);  // Acceder a la cola de mensajes con la clave 1234
    struct msqid_ds buf;

    // Obtener el estado de la cola
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Número de mensajes en la cola: %lu\n", buf.msg_qnum);
    printf("Tamaño máximo de la cola: %lu\n", buf.msg_qbytes);
    return 0;
}
