CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./ -pthread

all: clean productor consumidor main

clean:
	rm -f *.o *.txt productor consumidor 

productor:
	$(CC) -o productor productor.c semaforos.c clave.c archivos.c funciones.c memoria.c cola.c def.h

consumidor:
	$(CC) -o consumidor consumidor.c semaforos.c clave.c archivos.c funciones.c memoria.c cola.c def.h

main:
	$(CC) -o main main.c