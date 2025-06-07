CC = gcc
HEADERS = --pedantic-errors -Wall -O3 

all: clean equipo marcador main

clean:
	rm -f *.o *.txt equipo marcador 

equipo:
	$(CC) -o equipo equipo.c semaforos.c clave.c archivos.c funciones.c def.h

marcador:
	$(CC) -o marcador marcador.c semaforos.c clave.c archivos.c funciones.c def.h

main:
	$(CC) -o main main.c