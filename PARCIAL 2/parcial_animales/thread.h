#ifndef _JUGADOR_THREAD
#define _JUGADOR_THREAD

/*declaro la estructura pra ser usada por los threads*/
typedef struct tipo_thread tthread;
struct tipo_thread
{
	int nro_animal;
	int id_colamensaje;
	char nombre[50+1];
	int min_pasos;
	int max_pasos;
};

void *ThreadJugador (void *parametro);

#endif
