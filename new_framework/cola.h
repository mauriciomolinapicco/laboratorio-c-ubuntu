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


#endif