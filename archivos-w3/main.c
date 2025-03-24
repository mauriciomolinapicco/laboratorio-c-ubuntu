#include "archivos.h"
#include "productos.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(int argc, char *argv[]){
	int cantProductos = 10;
	producirProductos(cantProductos);
	consumirProductos();
	return 0;
}

