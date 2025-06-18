#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "archivos.h"
#include "def.h"

FILE *fp;
int inAbrirArchivo(char *szNombre,char *szModo){
	fp=fopen(szNombre, szModo);

	if(fp==NULL){
		return FALSE;	
	}
	else{
		return TRUE;
	}
}

void voCerrarArchivo(void){
	fclose(fp);
}

int inLeerArchivo(char *szTextoADevolver, int sizeTexto){
	char *leyendo;
	leyendo = fgets(szTextoADevolver, sizeTexto, fp);
	if(leyendo==NULL){
		return FALSE;	
	} else {
		return TRUE;
	}
}


int inEscribirArchivo(char *szTexto){
	return fprintf(fp, "%s", szTexto);
}

int inFinArchivo(void){
	return feof(fp);
}

int inRenombrarArchivo(char *szNombreViejo, char *szNombreNuevo){
	return rename(szNombreViejo, szNombreNuevo);
}

