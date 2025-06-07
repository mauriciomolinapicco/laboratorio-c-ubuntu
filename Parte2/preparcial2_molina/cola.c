#include "cola.h"
#include "clave.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>


int creo_id_cola_mensajes(int clave) {
  int id_cola_mensajes = msgget(creo_clave(clave), 0600 | IPC_CREAT);
  if (id_cola_mensajes == -1) {
    printf("Error al obtener identificador para cola mensajes\n");
    exit(-1);
  }
  return id_cola_mensajes;
}

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte,
                   int rIntEvento, char *rpCharMsg) {
  mensaje msg;
  int size;
  msg.long_dest = rLongDest;

  msg.int_rte = rIntRte;
  msg.int_evento = rIntEvento;
  strcpy(msg.char_mensaje, rpCharMsg);

  size =
      sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje);

  return msgsnd(id_cola_mensajes, (struct msgbuf *)&msg, size, IPC_NOWAIT);
}

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje *rMsg) {
  mensaje msg;
  int res;
  int size;

  size =
      sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje);

  res = msgrcv(id_cola_mensajes, (struct msgbuf *)&msg, size, rLongDest, 0);

  rMsg->long_dest = msg.long_dest;
  rMsg->int_rte = msg.int_rte;
  rMsg->int_evento = msg.int_evento;

  strcpy(rMsg->char_mensaje, msg.char_mensaje);

  return res;
}

int borrar_cola_de_mensajes(int Id_Cola_Mensajes) {
  msgctl(Id_Cola_Mensajes, IPC_RMID, (struct msqid_ds *)NULL);
  return 0;
}

int borrar_mensajes(int id_cola_mensajes) {
  mensaje Un_Mensaje;
  int res;
  do {
    res = msgrcv(id_cola_mensajes, (struct msgbuf *)&Un_Mensaje,
                 sizeof(Un_Mensaje.int_rte) + sizeof(Un_Mensaje.int_evento) +
                     sizeof(Un_Mensaje.char_mensaje),
                 0, IPC_NOWAIT);

  } while (res > 0);
  return res;
}
