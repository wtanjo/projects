#include <stdio.h>
#include <stdlib.h>
#include "mine.h"

int main() {
    int *arr = getArray();
    int n = _msize((void*)arr) / sizeof(arr[0]);
    int temp, j;
    for(int i = 1; i < n; i++){
        if(arr[i]<arr[i-1]){
            temp=arr[i];
            for(j=i-1;j>=0&&temp<arr[j];j--)
            {
                arr[j+1]=arr[j];
            }
            arr[j+1]=temp;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free((void *)arr);
    return 0;
}