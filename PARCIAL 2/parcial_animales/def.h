#ifndef _DEF
#define _DEF

#define TRUE 1
#define FALSE 0

#define ROJO 0
#define VERDE 1
#define CLAVE_BASE 33
#define LARGO_TMENSAJE 225

typedef struct{
	int nro;
} numero;

#define META 117
#define CANTIDAD 3
#define ESPERA 300

typedef enum
{
	MSG_NADIE,
	MSG_PANEL,
	MSG_ANIMAL
} Destinos;

typedef enum
{
	EVT_NINGUNO,
	EVT_INIT,
	EVT_AVANZO,
	EVT_CONTINUAR,
	EVT_FIN
} Eventos;

typedef struct {
	char nombre[50+1];
	int cant_veces_pasos;
	int cant_pasos;
} animal;

#endif
