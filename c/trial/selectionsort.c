#include <stdio.h>
#include <stdlib.h>
#include "mine.h"

int main() {
    int *arr = getArray();
    int n = _msize((void *)arr)/sizeof(arr[0]);
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free((void*)arr);
    return 0;
}