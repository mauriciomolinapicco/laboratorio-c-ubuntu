#include <pthread.h> // Libreria Hilos para C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Necesario para la función sleep()

#define CANTIDAD 10

// Variable global para semáforo (Mutex)
pthread_mutex_t mutex;

// La función para hilo siempre tiene que
// ser del tipo void* y recibir únicamente
// un solo parámetro del tipo void*
void *funcionThread(void *parametro)
{
    // lógica o tarea del hilo.
    int i;
    printf("Hijo\n");
    for (i = 0; i < CANTIDAD; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("Soy el hijo y tengo el mutex\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("Soy el hijo y espero 10 seg\n");
    sleep(10);
    printf("Hijo : Termino\n");
    pthread_exit((void *)"Listo");
}

int main()
{
    // Los tipos de datos están definidos en
    // la librería pthread.
    pthread_t idHilo;
    pthread_attr_t atributos;
    int error;
    int i;
    char *valorDevuelto = NULL;

    // Inicializo el semáforo (mutex)
    pthread_mutex_init(&mutex, NULL);

    // Inicializo los atributos del hilo.
    pthread_attr_init(&atributos);

    // Seteo el estado inicial del hilo.
    // PTHREAD_CREATE_JOINABLE indica que voy a esperar la finalización
    // del hilo. Esto me permite usar la función pthread_join() que está
    // más abajo.
    pthread_attr_setdetachstate(&atributos, PTHREAD_CREATE_JOINABLE);

    // pthread_create lanza el hilo. Le paso como parámetro:
    // idHilo ---> se carga cuando se crea el hilo.
    // atributos ---> los atributos del hilo.
    // funcionThread ---> es el nombre de la función que se va a ejecutar
    // al crear el hilo.
    // NULL ---> iría la dirección de memoria que recibe como parámetro
    // la función del hilo (void *parametro).
    if (pthread_create(&idHilo, &atributos, funcionThread, NULL) != 0)
    {
        perror("No puedo crear thread");
        exit(-1);
    }

    // Mientras se ejecutan los hilos continúa ejecutándose el main.
    for (i = 0; i < CANTIDAD; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("Soy el padre y tengo el mutex\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    printf("Padre : Espero al thread\n");

    // pthread_join es una función bloqueante que evita que
    // finalice el main(). Se desbloquea cuando van finalizando
    // los hilos. Le paso el idHilo que tiene que esperar.
    // Cada idHilo es único para cada hilo.
    pthread_join(idHilo, (void **)&valorDevuelto);

    printf("Padre : Ya ha terminado el thread\n");
    printf("Padre : devuelve \"%s\"\n", valorDevuelto);

    return 0;
}
