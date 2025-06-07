#include "archivos.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

FILE *fp;

int abrirArchivo(char *nombre, char *modo) {
	fp = fopen(nombre,modo);
	if(fp != NULL) {
		printf("Abriendo archivo...\n");
		return 1;	
	}
	printf("Error al abrir el archivo\n");
	return 0;
}

void escribirArchivo(char *contenido) {
	if(fp!=NULL){
		fprintf(fp, "%s", contenido);	
	}
}


char* leerArchivo(){
	static char linea[50];

	if(fp==NULL){
		return NULL;
	}
	if (!feof(fp)){
		fscanf(fp,"%s",linea);
		return linea;
	}
	return NULL;
}

void cerrarArchivo(){
	if(fp != NULL){
		fclose(fp);		
	}
}
