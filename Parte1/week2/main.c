#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[])
{	
	int inNumero=0;
	int rand;
	int *inDinamicoNum;	
	char *szDinamico;

	inDinamicoNum=(int*)malloc(sizeof(int)*1);
	szDinamico=(char*)malloc(sizeof(char)*(30+1));

	printf("\nNombre programa: %s", argv[0]);

	if(argc==2) { 
		inNumero=atoi(argv[1]); 
	};
	
	szDinamico[0]='F';
	szDinamico[1]='R'; 
	strcpy(&szDinamico[2],"pepe");

	printf("\nMuestro szDinamico: %s - %02x \n", szDinamico, &szDinamico);
	printf("\nEnteros (inNumero): %d - %02x - %d \n", inNumero, inNumero, &inNumero);
	
	voMostrar(&inNumero,szDinamico[0]);
	printf("\nNumero estatico: %d \n", inNumero);
	
	*inDinamicoNum=10;
	printf("\nEntero Dinamico: %d - %d - %02x \n", inDinamicoNum, *inDinamicoNum, &inDinamicoNum);

	free(inDinamicoNum);
	free(szDinamico);

	showMessage();

	rand=getRandomNumber(10, 20);
	printf("El numero aleatorio es: %d",rand);

	return 0;
}
