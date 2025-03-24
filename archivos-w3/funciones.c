#include "string.h"
#include "funciones.h"

FILE *archivo;

int abrirArchivo(char *nombreArchivo, char modo) {
	archivo = fopen(nombreArchivo, modo);
	
};


void escribirArchivo(char *contenido) {
	fprintf(archivo, );
};

char leerArchivo() {
	
};


void cerrarArchivo() {
	fclose(archivo);
};

