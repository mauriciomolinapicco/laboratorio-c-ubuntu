CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean jugadores panel

jugadores: 
	$(CC) -o jugadores $(HEADERS) jugadores.c funciones.c cola.c clave.c memoria.c archivos.c semaforos.c global.c thread.c -pthread

panel: 
	$(CC) -o panel $(HEADERS) panel.c funciones.c cola.c clave.c memoria.c archivos.c semaforos.c global.c

clean: 
	rm -rf *o panel jugadores *~
