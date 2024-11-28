#include <stdio.h>
#include "mine.h"

int main() {
    int *arr = getintArray();
    free((void*)arr);
    return 0;
}

void quicksort(int array[], int low, int high) {
    int i = low; 
    int j = high;
    if(i >= j) {
        return;
    }
 
    int temp = array[low];
    while(i != j) {
        while(array[j] >= temp && i < j) {
            j--;
        }
	while(array[i] <= temp && i < j) {
            i++;
        }
	if(i < j) {
            swap(array[i], array[j]);
        }
    }
 
    //����׼temp�����Լ���λ�ã�����i��λ�ã�
    swap(array[low], array[i]);
    QuickSort(array, low, i - 1);
    QuickSort(array, i + 1, high);
}