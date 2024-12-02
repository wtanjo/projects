#include <stdio.h>
#include "mine.h"

int binary_search(int *arr, int l, int r, int k);

int main() {
    int *arr = getSuitableIntArray();//输入一个非降序数组(非降序数组是指一个数组中的元素按从小到大的顺序排列，或者相等的元素可以相邻排列)
    int n = _msize((void*)arr) / sizeof(arr[0]);
    int k;
    scanf("%d", &k);
    printf("%d", binary_search(arr, 0, n-1, k));
    free((void*)arr);
    return 0;
}

int binary_search(int *arr, int l, int r, int k) {//l=left, r=right
    if (l+1 == r) {
        if (arr[l] >= k)
            return l;
        else if (arr[r] >= k)
            return r;
        else
            return r+1;//若不存在k，最后的r必为n-1
    }
    int mid = (l + r) / 2;
    if (arr[mid] >= k) 
        return binary_search(arr, l, mid, k);
    else
        return binary_search(arr, mid+1, r, k);
}