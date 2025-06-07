#include "stdio.h"
#include "string.h"

typedef struct Persona {
    char nombre[50]; //max 50 caracteres
    int edad;
    float altura;
} Persona;

void print_data(struct Persona *p) {
    printf("%s\n", p->nombre);
    printf("%d\n", p->edad);
    printf("%.2f\n", p->altura);
}

int main(int inc, char *argv[]) {
    Persona p1;
    Persona *p = &p1;

    // strcpy((*p).nombre, "Mauricio"); 
    // (*p).edad = 22;
    // (*p).altura = 1.78;

    strcpy(p->nombre, "Mauricio"); 
    p->edad = 22;
    p->altura = 1.78;


    print_data(p);
    return 0;
}