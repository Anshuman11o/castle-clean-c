#include <stdio.h>

#define MAX_DEPTH 200

void print(int i, int counter) {
    printf("i = %d\n", i);
    if (counter >= MAX_DEPTH) {
        perror("Depth limit reached");
        return;
    }
    print(i, counter + 1);
}

int main() {
    print(0, 0);
    return 0;
}
