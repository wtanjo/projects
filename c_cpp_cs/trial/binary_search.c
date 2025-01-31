#include <stdio.h>
#include "mine.h"

int binary_search(int *arr, int l, int r, int k);

int main() {
    int *arr = getSuitableIntArray();//����һ���ǽ�������(�ǽ���������ָһ�������е�Ԫ�ذ���С�����˳�����У�������ȵ�Ԫ�ؿ�����������)
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
            return r+1;//��������k������r��Ϊn-1
    }
    int mid = (l + r) / 2;
    if (arr[mid] >= k) 
        return binary_search(arr, l, mid, k);
    else
        return binary_search(arr, mid+1, r, k);
}