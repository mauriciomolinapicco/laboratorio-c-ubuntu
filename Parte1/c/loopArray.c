#include <stdio.h>

int main(int inc, char *argv[]) {
    double prices[] = {5.0, 10.5, 12.8, 15.1};

    for (int i = 0; i < 7; i++) {
        printf("%.2lf\n", prices[i]);
    }
    return 0;
}