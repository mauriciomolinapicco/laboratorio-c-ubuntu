CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean peaje autos

peaje: 
	$(CC) -o peaje $(HEADERS) peaje.c funciones.c cola.c clave.c memoria.c semaforos.c global.c thread.c -pthread

autos: 
	$(CC) -o autos $(HEADERS) autos.c funciones.c cola.c clave.c memoria.c semaforos.c global.c

clean: 
	rm -rf *o autos peaje *~
