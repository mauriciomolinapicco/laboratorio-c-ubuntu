CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean votantes panel

votantes: 
	$(CC) -o votantes $(HEADERS) votantes.c funciones.c cola.c clave.c memoria.c semaforos.c global.c thread.c -pthread

panel: 
	$(CC) -o panel $(HEADERS) panel.c funciones.c cola.c clave.c memoria.c semaforos.c global.c

clean: 
	rm -rf *o panel votantes *~
