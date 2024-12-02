#include <stdio.h>
int c = 4;

void func() {
    static int c = 5;
}

int main() {
    func();
    printf("%d", c);
    return 0;
}