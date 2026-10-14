#include <stdio.h>

#define DIVISOR 3

int main() {
    int input = 0;

    printf("Enter input: ");
    scanf("%9d", &input);

    printf("Result: %d\n", input / DIVISOR);

    return 0;
}
