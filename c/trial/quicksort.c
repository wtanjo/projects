#include <stdio.h>
#include "mine.h"

void quicksort(int *arr, int start, int end);

int main() {
    int *arr = getintArray();
    int n = _msize((void*)arr)/sizeof(arr[0]);
    quicksort(arr, 0, n-1);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    free((void*)arr);
    return 0;
}

void quicksort(int *arr, int l, int r) {//l(left)Ϊ������ʼλ�ã�r(right)Ϊ������ֹλ�ã�ȫ����������l=0,r=n-1
    int i = l, j = r;
    int base = arr[l];//���û�׼ֵ
    if (l >= r) {
        return;
    }
    while (i < j) {
        while(j > i) {
            if (arr[j] < base) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                break;
            }
            j--;
        }
        while (i < j) {
            if (arr[i] > base) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                break;
            }
            i++;
        }
    }
    quicksort(arr, l, i - 1);
    quicksort(arr, i + 1, r);
}