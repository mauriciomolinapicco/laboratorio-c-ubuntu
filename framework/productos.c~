#include "productos.h"
#include "archivos.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define FILE_NAME "producto.txt"

void producirProductos(int cantidad) {
	int i = 1;
	char contenido[50];
	int a = abrirArchivo(FILE_NAME,"w");
	if (a==0){
		return;	
	}
	
	for (i; i<=cantidad; i++){
		
		sprintf(contenido, "PRODUCTO-%02d\n",i);
		escribirArchivo(contenido);
	}

	cerrarArchivo(contenido);
	printf("Productos cargados...\n");
}


void consumirProductos(){
	char *linea;
	int a = abrirArchivo(FILE_NAME,"r");
	if (a==0){return;}
	
	linea = leerArchivo();	
	printf("Consumiendo productos...\n");
	while (linea != NULL){
		printf("%s\n",linea);
		linea = leerArchivo();
	}
	cerrarArchivo();
	printf("Productos consumidos\n");
}


