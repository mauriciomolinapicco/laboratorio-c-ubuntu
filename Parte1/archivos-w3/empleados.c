#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[]) 
{
int legajo;
char nombre[15];
float sueldo;
FILE *fp;

fp=fopen("empleados.txt","w");

if (fp == NULL) {
	printf("No se puede abrir el archivo");
	return 1;
}

printf("Ingrese legajo: \n");
scanf("%d", &legajo);

while (legajo != 0) {
	printf("INgrese nombre: \n");
	scanf("%s", &nombre);
	printf("Ingrese sueldo: \n");
	scanf("%f", &sueldo);
	fprintf(fp,"%d %s %.2f\n",legajo,nombre,sueldo);
	printf("Ingrese legajo: \n");
	scanf("%d", &legajo);
}

fclose(fp);
}
