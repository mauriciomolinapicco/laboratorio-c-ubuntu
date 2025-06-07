#include "stdio.h"

void myfunc() {
    printf("im in a function\n");
};

void say_name(char name[], int age) {
    printf("Hello %s, you are %d yeard old!\n", name, age);
}


int main() {
    char name[] = "Mauricio";
    int age = 22;

    say_name(name, age);

    myfunc();
}