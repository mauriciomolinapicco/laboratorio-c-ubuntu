/*
2016.04.11 Se unifico funcion de creo_memoria
*/

#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semaforo.h"
#include "memoria.h"
#define ROJO 0
#define VERDE 1

#define CANTIDAD 10
#define CANTIDAD_TOTAL 10
#define DESDE 0
#define HASTA 25
#define CLAVE_BASE 33


typedef struct tipo_dato dato;

struct tipo_dato
{
	int numero;//4 byte
     char letra;// 1 byte
        //5 byte la structura
};


int main()
{
	dato *memoria = NULL;
	int id_memoria;
	int i, aleatorio;
	int id_semaforo;

	srand(time(NULL));//cambia la semilla para random,  usa el time como semilla inicial

	id_semaforo = creo_semaforo();
	
	inicia_semaforo(id_semaforo, VERDE);

	memoria = (dato*)creo_memoria(sizeof(dato)*CANTIDAD, &id_memoria, CLAVE_BASE);
	
	//
	//	Ya podemos utilizar la memoria.
	//

	while(CANTIDAD_TOTAL)
	{
		espera_semaforo(id_semaforo);		
			printf("Escribimos en la memoria\n");
			for (i=0; i<CANTIDAD; i++)
			{
				aleatorio = rand()%(HASTA-DESDE)+DESDE;
				memoria[i].numero = aleatorio ;
				memoria[i].letra  = 0x41 + aleatorio ;
				printf("Escrito %d %c\n", memoria[i].numero, memoria[i].letra);
				sleep (1);
			}
			printf("Dejamos de escribir en la memoria\n");
		levanta_semaforo(id_semaforo);
		sleep (10);
	}
	//
	//	Terminada de usar la memoria compartida, la liberamos.
	//
	shmdt ((char *)memoria);
	shmctl (id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
	return 0;
}
