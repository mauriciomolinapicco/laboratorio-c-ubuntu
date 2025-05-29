#ifndef COLA_H
#define COLA_H

#define LARGO_MENSAJE 50

typedef struct
{
	long	long_dest; 						/*Destinatario*/
	int 	int_rte;						/*Remitente*/
	int 	int_evento;						/*Numero de evento*/ 
	char 	char_mensaje[LARGO_MENSAJE];	/*mensajse*/
} mensaje;

int creo_id_cola_mensajes(int clave);

int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg);

int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg);

int borrar_mensajes(int id_cola_mensajes);

int borrar_cola_mensajes(int id_cola_mensajes);

#endif