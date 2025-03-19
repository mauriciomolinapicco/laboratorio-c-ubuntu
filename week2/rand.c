#include "stdio.h"

int main() {
	int a;
	srand(time(NULL));
	
	a = rand() % (50-40+1)+40;

	printf("Nro aleatorio entre 40 y 50 %d\n", a);
}