#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mine.h"

void swap(char *a, char *b);
void print_full_permutations(char *str, int left, int right);

int main() {
    char *str = getSuitableString();
    int len = strlen(str);
    print_full_permutations(str, 0, len-1);
    free((void*)str);
    return 0;
}

void print_full_permutations(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str); // ������н��
    }
    else {
        for (int i = left; i <= right; i++) {
            swap((str + left), (str + i)); // ����
            print_full_permutations(str, left + 1, right); // �ݹ�����ȫ����
            swap((str + left), (str + i)); // ������ȥ���ָ�ԭʼ״̬
        }
    }
}

void swap(char *a, char *b) {// ���������ַ�
    char temp = *a;
    *a = *b;
    *b = temp;
}