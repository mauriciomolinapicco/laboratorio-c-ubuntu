#include "stdio.h"
#include "stdlib.h"
#include <string.h>

int main(int argc, char *argv[]) {
	int i=0;
	int j=0;
	char cadena[10];
	strcpy(cadena, "abcdjajsk");
	
	while (cadena[i] != '\0') {
		printf("%c", cadena[i]);
		i = i+1;
	}
	
	printf("%cUsando \\0: ", '\n');

	while (cadena[j] != '\0') {
		printf("Iteracion %d - ", j + 1);
		j = j+1;
	}

	printf("\nUsando sizeof: ");
	j=0;
	
	while (j < sizeof(cadena)) {
		printf("Iteracion %d - ",j+1);
		j=j+1;
	}

	printf("\nla longitud de la cadena es %d", sizeof(cadena));
	return 0;
}
