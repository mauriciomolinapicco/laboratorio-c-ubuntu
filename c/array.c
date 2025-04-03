#include <stdio.h>

int main(int inc, char *argv[]) {
    double prices[] = {5.0, 10.0, 15.5, 20.0};

    // char name[] = "Mauri"; //array of chars

    printf("%.2lf\n", prices[1]);

    int ages[5];
    ages[0] = 10;
    printf("%i\n",ages[0]); //10

    return 0;
}