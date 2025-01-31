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
        printf("%s\n", str); // 输出排列结果
    }
    else {
        for (int i = left; i <= right; i++) {
            swap((str + left), (str + i)); // 交换
            print_full_permutations(str, left + 1, right); // 递归生成全排列
            swap((str + left), (str + i)); // 交换回去，恢复原始状态
        }
    }
}

void swap(char *a, char *b) {// 交换两个字符
    char temp = *a;
    *a = *b;
    *b = temp;
}