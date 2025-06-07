CC = gcc
HEADERS = --pedantic-errors -Wall -O3 

all: clean productor consumidor

clean:
	rm -f *.o *.txt productor consumidor

productor:
	$(CC) -o productor productor.c semaforos.c clave.c archivos.c funciones.c def.h

consumidor:
	$(CC) -o consumidor consumidor.c semaforos.c clave.c archivos.c funciones.c def.h