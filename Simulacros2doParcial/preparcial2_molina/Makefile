CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./

all: clean animales cancha

animales: 
	$(CC) -o animales $(HEADERS) animales.c funciones.c cola.c clave.c global.c thread.c -pthread

cancha: 
	$(CC) -o cancha $(HEADERS) cancha.c funciones.c cola.c clave.c global.c

clean: 
	rm -rf *o cancha animales *~
