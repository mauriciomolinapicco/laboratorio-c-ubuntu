#include <stdio.h>

struct perro { //parecido a una clase
    char nombre[30]; //longitud maxima=30
    int edad;
    float peso;
} perro1={"Firulais",10,3.5},
perro2={"Bunky", 5, 25.9}; //variables de las estructuras


int main(int inc, char *argv[]) {
    printf("El nombre de mi mascota es: %s \n", perro1.nombre);
    printf("El peso de %s es: %.2f y tiene %i meses", perro1.nombre, perro1.peso, perro1.edad);
    return 0;
}