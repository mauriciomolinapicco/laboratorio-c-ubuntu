CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean jugador revolver

jugador: 
	$(CC) -o jugador $(HEADERS) jugador.c funciones.c cola.c clave.c global.c thread.c -pthread

revolver: 
	$(CC) -o revolver $(HEADERS) revolver.c funciones.c cola.c clave.c global.c

clean: 
	rm -rf *o revolver jugador *~
