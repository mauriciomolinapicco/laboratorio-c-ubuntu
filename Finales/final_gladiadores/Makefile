CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean luchadores coliseo

luchadores: 
	$(CC) -o luchadores $(HEADERS) luchadores.c funciones.c cola.c clave.c memoria.c archivos.c semaforos.c global.c thread.c -pthread

coliseo: 
	$(CC) -o coliseo $(HEADERS) coliseo.c funciones.c cola.c clave.c memoria.c archivos.c semaforos.c global.c

clean: 
	rm -rf *o coliseo luchadores *~
