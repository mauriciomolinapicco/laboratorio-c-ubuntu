#include <sys/ipc.h>

key_t creo_clave()
{
	key_t clave;
	clave = ftok("/bin/echo",33);
	if (clave == (key_t)-1) {
		printf("No se pudo conseguir la clave \n");
		exit(0);
	}
	return clave;
}
