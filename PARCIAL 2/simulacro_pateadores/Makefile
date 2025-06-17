CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean pateadores arquero

pateadores: 
	$(CC) -o pateadores $(HEADERS) pateadores.c funciones.c cola.c clave.c memoria.c semaforos.c global.c thread.c -pthread

arquero: 
	$(CC) -o arquero $(HEADERS) arquero.c funciones.c cola.c clave.c memoria.c semaforos.c global.c

clean: 
	rm -rf *o arquero pateadores *~
