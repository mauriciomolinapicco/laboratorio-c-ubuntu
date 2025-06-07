#include <stdio.h>
#include <math.h>

int main() {
    double A;
    double B;
    double C;

    printf("Ingrese los lados: ");
    scanf("%lf", &A);
    scanf("%lf", &B);

    C = sqrt(A*A + B*B);

    printf("La hipotenusa es: %lf", C);

}