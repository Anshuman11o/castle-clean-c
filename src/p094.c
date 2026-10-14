#include <stdio.h>
#include <stdlib.h>

int* generateAlwaysNonNullResult() {
    return NULL;
}

int main() {
    int* a = generateAlwaysNonNullResult();
    printf("AlwaysNonNullResult: %d\n", *a);

    return 0;
}
