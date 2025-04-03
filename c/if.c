#include "stdio.h"

int main() {
    int age;

    printf("Enter age");
    scanf("%d", &age);

    if (age >= 18) {
        printf("You are an adult");
    } else if (age < 0) {
        printf("you havent been born yet bro");
    }
    return 0;
}