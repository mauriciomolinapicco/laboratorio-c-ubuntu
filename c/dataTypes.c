#include <stdio.h>
#include <stdbool.h>

int main() {
    char a = 'C'; // %c
    char b[] = "Mauricio";  // %s

    float c = 10.2;  //%f
    double d = 3.1415788862; // %lf

    bool e = true; // %d

    printf("%d", e);    //salida: 1

    //For chars i can store the ASCII value
    // 1 byte from -128 to 127
    char f = 100; // %d or %c
    printf("The char with d is %d\n", f); // 100
    printf("The char with c is %c\n", f); // d
    /*
    unsigned char myChar = 50; hace que el rango sea de 0 a 256
    */

    //short int (2 bytes)   from -32768 to 32767
    short i = 10000; 
    printf("the int is %d\n", i);

    //long int
    long int l = 90900900;
    printf("The long int is %ld", l);
}