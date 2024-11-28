#include <stdio.h>
#include <stdlib.h>
#define N 1000

int *getintArray() {
    int *arr0 = (int*)malloc(N*sizeof(int));
    int i = 0;
    for (i = 0; i < N; i++) {
        scanf("%d", &arr0[i]);
        if (getchar() == '\n') 
            break;
    }
    int *arr = (int*)realloc((void*)arr0, (i+1)*sizeof(int));
    arr0 = NULL;
    free((void*)arr0); 
    return arr;
}
//记得最后free((void*)arr)