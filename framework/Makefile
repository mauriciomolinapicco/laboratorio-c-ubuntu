HEADER = -I./
CC = gcc
CFLAGS = -Wall -pedantic-errors -std=gnu89 -O3


all: clean programa

clean:
	rm -f *.o prog

programa:
	$(CC) -o prog $(CFLAGS) $(HEADER) main.c archivos.c productos.c clave.c -pthread
