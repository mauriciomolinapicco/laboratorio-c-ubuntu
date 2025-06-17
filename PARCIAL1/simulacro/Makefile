CC = gcc
CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./

all: clean productor consumidor

productor:
		$(CC) -o productor $(CFLAGS) $(HEADERS) productor.c archivos.c semaforos.c funciones.c clave.c def.h 

consumidor:
		$(CC) -o consumidor $(CFLAGS) $(HEADERS) consumidor.c archivos.c semaforos.c funciones.c clave.c def.h 

clean:
		rm -f *.o productor consumidor menu.txt