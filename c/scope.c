#include <stdio.h> 

void wrong_swap(int a, int b);
void swap(int *a, int *b);

int main(void) 
{
    int a = 10;
    int b = 5;

    printf("a: %d b:%d\n", a,b);
    wrong_swap(a,b);
    printf("a: %d b:%d\n", a,b); //no los cambio
    
    swap(&a,&b);
    printf("a: %d b:%d\n", a,b); //ahora si los cambio, porque le mande la REFERENCIA

}

void wrong_swap(int a, int b)
{ 
    //INCORRECTO, NO va a cambiar las variables que le mande
    // ya que se esta haciendo una copia y no estoy referenciando los valores q
    // que quiero cambiar
    int tmp = a;
    a = b;
    b = tmp;
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}