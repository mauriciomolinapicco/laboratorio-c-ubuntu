#ifndef _MENSAJES
#define _MENSAJES
#include "def.h"


typedef struct tipo_mensajes mensaje;
struct tipo_mensajes
{
	long	long_dest; 						/*Destinatario*/
	int 	int_rte;						/*Remitente*/
	int 	int_evento;						/*Numero de nevento*/
	char 	char_mensaje[LARGO_TMENSAJE];	/*mensajse*/
};

int creo_id_cola_mensajes(void);
int enviar_mensaje(int id_cola_mensajes, long rLongDest, int rIntRte, int rIntEvento, char* rpCharMsg);
int recibir_mensaje(int id_cola_mensajes, long rLongDest, mensaje* rMsg);
int borrar_mensajes(int id_cola_mensajes);
int borrar_cola_de_mensajes(int Id_Cola_Mensajes);

#endif
