#include <stdio.h>
#include <math.h>
#include <TXLib.h>
main() {
    float a, b, c;
    printf("¬ведите a, b, c: ");
    scanf("%f %f %f", &a, &b, &c);
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("x - любое число");
            } else {
                printf("корней нет");
            }
        } else {
            printf ("x = %g", - c / b);
        }
    } else {
        float D, x1, x2;
        D = b * b - 4 * a * c;
        if (D < 0) {
            printf("корней нет");
        } else {
            if (D == 0) {
                x1 = - b / (2 * a);
                printf("x = %g", x1);
            } else {
                x1 = (- b + sqrt(D)) / (2 * a);
                x2 = (- b - sqrt(D)) / (2 * a);
                printf("x1 = %g, x2 = %g", x1, x2);
            }
        }
    }
    return 0;
}
