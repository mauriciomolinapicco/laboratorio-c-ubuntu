CC = gcc
HEADERS = --pedantic-errors -Wall -O3 

all: clean avion panel

clean:
	rm -f *.o *.txt avion panel

avion:
	$(CC) -o avion avion.c semaforos.c clave.c archivos.c funciones.c def.h


panel:
	$(CC) -o panel panel.c semaforos.c clave.c archivos.c funciones.c def.h

