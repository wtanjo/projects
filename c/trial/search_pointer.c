#include <stdio.h>
#include "mine.h"

int *search_pointer(int *arr, int n, int key);

int main() {
    int *arr = getintArray();
    int n = _msize((void*)arr)/sizeof(arr[0]);
    int key;
    scanf("%d", &key);
    if (search_pointer(arr, n, key) != NULL) 
        printf("µØÖ·£º%d", search_pointer(arr, n, key));
    else 
        printf("²»´æÔÚ");
    free((void*)arr);
    return 0;
}

int *search_pointer(int *arr, int n, int key) {
    int *p;
    p = arr;
    for (;p < arr + n; p++) {
        if (*p == key) 
            return p;
    }
    return NULL;
}