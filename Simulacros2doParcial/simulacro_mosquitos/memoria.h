#ifndef _MEMORIA
#define _MEMORIA

void* creo_memoria(int size, int* r_id_memoria, int clave_base);

void liberar_memoria(int id_memoria, char *memoria);

#endif
