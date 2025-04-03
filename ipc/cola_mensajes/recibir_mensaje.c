#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura del mensaje
struct msg_buffer {
    long mtype;     // Tipo de mensaje
    char mtext[100]; // Datos del mensaje
};

int main() {
    key_t key = ftok("archivo.txt", 65);  
    int msqid = msgget(key, 0666);

    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    struct msg_buffer message;

    // Recibir un mensaje de tipo 1
    ssize_t msg_len = msgrcv(msqid, &message, sizeof(message.mtext), 1, 0);

    if (msg_len == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Mensaje recibido: %s\n", message.mtext);

    return 0;
}
