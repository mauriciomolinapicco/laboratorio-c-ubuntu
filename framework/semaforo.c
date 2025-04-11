#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

//pasar a def.h todos estos
#define CLAVE_BASE 33 
#define ROJO 0
#define VERDE 1

int creo_semaforo()
{
    key_t clave = creo_clave(CLAVE_BASE);
    int id_semaforo = semget(clave, 1, 0600|IPC_CREAT);
    /* PARAMETROS
        clave, cant semaforo, 0600 lo usa cualquiera, IPC es constante
    */
   if(id_semaforo == -1)
   {
    printf("Error: no se pudo crear semaforo\n");
    exit(0);
   }
   return id_semaforo;
}


void inicia_semaforo(int id_semaforo, int valor)
{
    semctl(id_semaforo, 0, SETVAL, valor);
}


void levanta_semaforo(int id_semaforo)
{
    struct sembuf operacion;
    printf("LEVANTA SEMAFORO");
    operacion.sem_num = 0;
    operacion.sem_op = 1; //incrementa el semaforo en 1
    operacion.sem_flg = 0;
    semop(id_semaforo,&operacion,1);
}


void espera_semaforo(int id_semaforo)
{
    struct sembuf operacion;
    printf("ESPERA SEMAFORO\n");
    operacion.sem_num = 0;
    operacion.sem_op = -1; //decremeta el semaforo en 1
    operacion.sem_flg = 0;
    semop(id_semaforo,&operacion);
}