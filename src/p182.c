#include <stdio.h>
#include <stdlib.h>

int isPowerOfTwo(unsigned int n) {
    return (n && !(n & (n - 1)));
}

void swap(unsigned int* a_ptr, unsigned int* b_ptr) {
    if (*a_ptr != *b_ptr) {
        *a_ptr ^= *b_ptr;
        *b_ptr ^= *a_ptr;
        *a_ptr ^= *b_ptr;
    }
}

int countSetBits(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int maximum(int x, int y) {
    return x ^ ((x ^ y) & -(x < y));
}

int main() {
    unsigned int x = 15, y = 20;

    if (isPowerOfTwo(x))
        printf("%u is power of 2\n", x);
    else
        printf("%u is not power of 2\n", x);

    printf("Before swap: x = %u, y = %u\n", x, y);
    swap(&x, &y);
    printf("After swap: x = %u, y = %u\n", x, y);

    printf("Number of set bits in %u is %d\n", x, countSetBits(x));

    printf("The maximum of %d and %d is %d\n", 32, 56, maximum(32, 56));

    return 0;
}
