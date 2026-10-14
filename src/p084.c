#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double computeSqrt(double a) {
    assert(a >= 0);
    if (a < 0) {
        return 0;
    }
    return sqrt(a);
}

int main() {
    const double a = 3.14, b = -2.7;

    printf("Sqrt of %f is %f\n", a, computeSqrt(a));
    printf("Sqrt of %f is %f\n", b, computeSqrt(b));

    return 0;
}
