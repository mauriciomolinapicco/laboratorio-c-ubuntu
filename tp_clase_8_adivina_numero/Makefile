CC = gcc
HEADERS = --pedantic-errors -Wall -O3 -I./ -pthread
MISC = funciones.c global.c
all: clean adivino

clean:
	rm -f *.o *.txt adivino 

adivino:
	$(CC) -o adivino $(HEADERS) $(MISC) thread.c 
