CC = gcc-4.1
CFLAGS = -Wall -O3 -std=gnu89 -pedantic-errors
HEADERS = -I./

all: clean productor consumidor

productor: productor.c archivos.c funciones.c semaforo.c clave.c def.h archivos.h funciones.h semaforo.h clave.h
	$(CC) -o productor productor.c archivos.c funciones.c semaforo.c clave.c $(CFLAGS) $(HEADERS)

consumidor: consumidor.c archivos.c funciones.c semaforo.c clave.c def.h archivos.h funciones.h semaforo.h clave.h
	$(CC) -o consumidor consumidor.c archivos.c funciones.c semaforo.c clave.c $(CFLAGS) $(HEADERS)

clean:
	rm -f productor consumidor medicamentos.txt
