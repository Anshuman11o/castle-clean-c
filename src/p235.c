#include <stdio.h>
#include <stdlib.h>

void square(int* a) {
    int b = *a;
    *a = b * b;
    free(a);
}

int main() {
    int *a = (int*) malloc(sizeof(int));

    if (a == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    *a = 5;
    square(a);
    printf("Result: %d\n", *a);

    return 0;
}
