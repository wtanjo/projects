#include <stdio.h>
#include <stdlib.h>
#include "mine.h"

char *SDdwP(char *str);

int main() {
    char *str = getSuitableString();
    char *newStr = SDdwP(str);
    printf("%s", newStr);
    free((void*)str);
    return 0;
}

char *SDdwP(char *str) {
    char *p = str;
    for (; *p != '\0'; p++) {
        for (char *q = p + 1; *q != '\0'; q++) {
            if (*p == *q) {
                for (char *r = q; *r != '\0'; r++) {
                    *r = *(r + 1);
                }
            }
        }
    }
    return str;
}