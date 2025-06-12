CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean jugadores pienso

jugadores: 
	$(CC) -o jugadores $(HEADERS) jugadores.c funciones.c cola.c clave.c memoria.c semaforos.c global.c thread.c -pthread

pienso: 
	$(CC) -o pienso $(HEADERS) pienso.c funciones.c cola.c clave.c memoria.c semaforos.c global.c

clean: 
	rm -rf *o pienso jugadores *~
