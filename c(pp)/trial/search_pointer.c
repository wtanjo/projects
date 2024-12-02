#include <stdio.h>
#include "mine.h"

void search_pointer(int *arr, int n, int key);

int main() {
    int *arr = getSuitableIntArray();
    int n = _msize((void*)arr)/sizeof(arr[0]);
    int key;
    scanf("%d", &key);
    search_pointer(arr, n, key);
    free((void*)arr);
    return 0;
}

void search_pointer(int *arr, int n, int key) {
    int *p = arr;
    for (;p < arr + n; p++) {
        if (*p == key) {
            printf("%d ", p);
        }
    }
}