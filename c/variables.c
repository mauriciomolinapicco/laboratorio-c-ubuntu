#include <stdio.h>

int main() {
    int x; //declaration
    x = 100; //initialization

    int age = 30; // declaration AND initialization
    char grade = 'A';
    char name[] = "Mauricio"; //Strings are arrays of single characters

    printf("Hello %s\n", name);
    printf("I am %d years old\n", age); //%d stands for decimal
    printf("My grade is %c", grade);

    return 0;
};