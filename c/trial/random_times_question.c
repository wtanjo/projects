#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void judge(int judgement);

int main() {
    int D, a, b;
    scanf("%d", &D);//DΪ�˷����п��ܳ��ֵ�������֣���һλ���˷�ȡD=9
    srand(time(NULL));//�������������
    a = 1 + rand() % D;//����1��D֮��������
    b = 1 + rand() % D;
    printf("%d * %d = ?\n", a, b);
    int result;
    scanf("%d", &result);//Сѧ��������
    judge(result == a * b);//�жϴ��Ƿ���ȷ����������
    return 0;
}

void judge(int judgement) {
    char true[][25] = {"Very good!", "Excellent!", "Keep up the good work!"};
    char false[][25] = {"No. Please try again.", "Wrong. Try once more.", "No. Keep trying."};
    srand(time(NULL));
    int choice = rand() % 3;//���ѡ��0~2֮���һ������(�������)
    if (judgement == 1) {
        printf("%s\n", true[choice]);
    }
    else {
        printf("%s\n", false[choice]);
    }
}