CC = gcc
HEADERS = --pedantic-errors -Wall -O3 

all: clean banco cajero

clean:
	rm -f *.o *.txt banco cajero 

banco:
	$(CC) -o banco banco.c clave.c funciones.c memoria.c cola.c def.h

cajero:
	$(CC) -o cajero cajero.c clave.c funciones.c memoria.c cola.c def.h
