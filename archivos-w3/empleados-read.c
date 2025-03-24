#include "stdlib.h"
#include "stdio.h"

int main(int argc, char *argv[]){
FILE *fp;
char nombre[20];
int legajo;
float sueldo;

fp = fopen("empleados.txt","r");
if (fp==NULL){
	printf("No se pudo abrir el archivo");
	return 1;
}

while(!feof(fp)){
	fscanf(fp,"%d %s %f",&legajo,&nombre,&sueldo);
	printf("Legajo %d Nombre %s Sueldo %.2f\n",legajo,nombre,sueldo);
}
fclose(fp);

return 0;
}
