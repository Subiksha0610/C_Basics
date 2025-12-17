#include <stdio.h>

int main() {
    char test[] = "A\t		B\bC\\";

    int i;
    for (i = 0; test[i] != '\0'; ++i) {
        int c = test[i];
        if (c == '\t') {
            printf("\\t");
        } else if (c == '\b') {
            printf("\\b");
        } else if (c == '\\') {
            printf("\\\\");
        } else {
            putchar(c);
        }
    }

    return 0;
}
