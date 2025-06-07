#include <stdio.h>
#include <string.h>

int main(void) {
    char *s = "hola";
    char *t = "chau";

    if (strcmp(s,t) == 0) {
        printf("Son iguales\n");
    } else {
        printf("no son iguales\n");
    }

    printf("%p\n", s); //por el %p me da la posicion de memoria
    printf("%p\n", t); 
}