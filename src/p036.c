#include <stdio.h>

int printArrayAt(int* arr, int size, int index) {
    if (index == size) {
        return 0;
    }

    printf("%d\n", arr[index]);
    return printArrayAt(arr, size, ++index);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int ret = printArrayAt(arr, 5, 0);
    printf("Ret: %d\n", ret);
    return 0;
}
