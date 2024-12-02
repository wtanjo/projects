#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void judge(int judgement);

int main() {
    int D, a, b;
    scanf("%d", &D);//D为乘法题中可能出现的最大数字，如一位数乘法取D=9
    srand(time(NULL));//设置随机数种子
    a = 1 + rand() % D;//生成1到D之间的随机数
    b = 1 + rand() % D;
    printf("%d * %d = ?\n", a, b);
    int result;
    scanf("%d", &result);//小学生输入解答
    judge(result == a * b);//判断答案是否正确并作出反馈
    return 0;
}

void judge(int judgement) {
    char true[][25] = {"Very good!", "Excellent!", "Keep up the good work!"};
    char false[][25] = {"No. Please try again.", "Wrong. Try once more.", "No. Keep trying."};
    srand(time(NULL));
    int choice = rand() % 3;//随机选择0~2之间的一个数字(反馈序号)
    if (judgement == 1) {
        printf("%s\n", true[choice]);
    }
    else {
        printf("%s\n", false[choice]);
    }
}