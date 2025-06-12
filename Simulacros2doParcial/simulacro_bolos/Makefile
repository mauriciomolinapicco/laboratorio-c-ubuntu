CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean jugadores bolera

jugadores: 
	$(CC) -o jugadores $(HEADERS) jugadores.c funciones.c cola.c clave.c memoria.c semaforos.c global.c thread.c -pthread

bolera: 
	$(CC) -o bolera $(HEADERS) bolera.c funciones.c cola.c clave.c memoria.c semaforos.c global.c

clean: 
	rm -rf *o bolera jugadores *~
