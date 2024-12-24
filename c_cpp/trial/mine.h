#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000

int *getSuitableIntArray() {
    int *arr0 = (int*)malloc(N*sizeof(int));
    int i = 0;
    for (i = 0; i < N; i++) {
        scanf("%d", &arr0[i]);
        if (getchar() == '\n') 
            break;
    }
    int *arr = (int*)realloc((void*)arr0, (i+1)*sizeof(int));
    free((void*)arr0);
    arr0 = NULL; //先free再赋值为NULL，防止指针悬空
    return arr;
}

char *getSuitableString() {
    char *str0 = (char*)malloc(N*sizeof(char));
    fgets(str0, N, stdin);
    int len = strlen(str0);
    char *str = (char*)realloc((void*)str0, len*sizeof(char));
    str[len-1] = '\0';
    free((void*)str0); 
    str0 = NULL;
    return str;
}
//记得最后free((void*)arr), free((void*)str)