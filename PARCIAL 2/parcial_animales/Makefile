#mi makefile

CC= gcc-4.1
CFLAGS= -pedantic-errors -Wall -O3 -std=gnu89 -pthread
PHEADER = -I./
MISC_1 = animales.c funciones.c semaforo.c archivos.c clave.c memoria.c mensajes.c thread.c global.c
MISC_2 = panel.c funciones.c semaforo.c archivos.c clave.c memoria.c mensajes.c global.c

all: clean programa1 programa2

programa1: animales.c semaforo.c semaforo.h funciones.c funciones.h clave.c clave.h archivos.c archivos.h memoria.c memoria.h def.h global.c global.h mensajes.c mensajes.h thread.c thread.h
	$(CC) -o animales $(MISC_1) $(CFLAGS) $(PHEADER)

programa2: panel.c semaforo.c semaforo.h funciones.c funciones.h clave.c clave.h archivos.c archivos.h memoria.c memoria.h def.h global.c global.h mensajes.c mensajes.h
	$(CC) -o panel $(MISC_2) $(CFLAGS) $(PHEADER)

clean:
	rm -rf *o panel animales
