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
    key_t key = ftok("archivo.txt", 65);  // Generar una clave única
    int msqid = msgget(key, 0666);  // Obtener el identificador de la cola de mensajes

    if (msqid == -1) {
        perror("msgget");
        return 1;
    }

    struct msg_buffer message;

    message.mtype = 1;  // Establecer el tipo de mensaje
    strcpy(message.mtext, "Hola, este es un mensaje.");  // Establecer los datos del mensaje

    // Enviar el mensaje a la cola de mensajes
    if (msgsnd(msqid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Mensaje enviado: %s\n", message.mtext);

    return 0;
}
