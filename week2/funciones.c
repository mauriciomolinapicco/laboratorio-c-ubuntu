#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "funciones.h"

void voMostrar(int *num, char *szVal){
	
	*num=55;
	printf("Muestro numero %d\n", num);
	printf("Muestro direccion y valor: %d %02x %02x \n",*num, *num, &num);
}

void showMessage() {
	printf("estoy en la funcion\n");
}

int getRandomNumber(int inf, int sup) {
	int num;
	srand(time(NULL));
	
	num = rand() % (sup-inf+1)+inf;
	return num;	
}