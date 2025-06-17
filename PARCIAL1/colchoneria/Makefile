CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean colchoneria vendedor main

clean:
	rm -f *.o *.txt colchoneria vendedor 

colchoneria:
	$(CC) -o colchoneria colchoneria.c semaforos.c clave.c funciones.c memoria.c def.h

vendedor:
	$(CC) -o vendedor vendedor.c semaforos.c clave.c funciones.c memoria.c def.h

main:
	$(CC) -o main main.c