#include <stdio.h>
//Funcion de ejemplo
void funcion()
{
    printf("Se ha entrado en la funcion\n");
}

int main()
{
    //Creamos el puntero a la funcion
    void (*puntero_funcion)() = &funcion;
    //Llamamos la funcion a traves del puntero
    puntero_funcion();
    return 0;
}