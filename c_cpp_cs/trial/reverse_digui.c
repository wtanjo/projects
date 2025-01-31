#include <stdio.h>
#include <math.h>

int reverse(int n);

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", reverse(n));
    return 0;
}

int reverse(int n) {
    int rev = n / pow(10, floor(log10(n)));
    if (n < 10)
        return n;
    else
        rev = rev + reverse(n % (int)pow(10, floor(log10(n)))) * 10;
    return rev;
}