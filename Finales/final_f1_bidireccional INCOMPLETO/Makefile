CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean autos panel

autos: 
	$(CC) -o autos $(HEADERS) autos.c funciones.c cola.c clave.c memoria.c archivos.c semaforos.c global.c thread.c -pthread

panel: 
	$(CC) -o panel $(HEADERS) panel.c funciones.c cola.c clave.c memoria.c archivos.c semaforos.c global.c

clean: 
	rm -rf *o panel autos *~
