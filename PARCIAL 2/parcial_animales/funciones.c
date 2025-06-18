#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "funciones.h"
#include "def.h"

int inMostrarPepe(void){
	printf("SOY PEPE\n");
	return 0;
}

int inDevolverAleatorio(int inDesde, int inHasta){
	int numero=0;
	numero=(rand()%(inHasta-inDesde+1)+inDesde);
	return numero;
}

int generarNumeroUnico(int inDesde, int inHasta, int numeros[]){
	int entero, esUnico, i;
	esUnico = FALSE;
	do{
		entero = inDevolverAleatorio(inDesde, inHasta);
		esUnico = 1;
		for(i=0;i<inHasta+1;i++){
			if(numeros[i] == entero){
				esUnico = 0;
				break;
			}
					
		}
	}while(!esUnico);
	return entero;
}

int inExisteEnLista(numero *listado, int num, int cantidad){
	int i=0;
	while(i<cantidad){
		if(num == listado[i].nro){
			return TRUE;
		}
		i++;
	}
	return FALSE;
}

