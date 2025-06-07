#include <stdio.h>

int main() {
    int x = 4;
    //integer named x is set to the value 4

    int *pX = &x; //stores the value of the memory position
    //integer pointer named pX is set to the address of x

    int y = *pX;
    // integer named y is set to the thing pointed to by pX

    printf("Valor de px: %d", pX); //612366256
    printf("Valor de y: %d", y);  //4
}