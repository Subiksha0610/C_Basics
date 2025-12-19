#include <stdio.h>

#define TABSTOP 8

int main(void) {
    int c, pos = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TABSTOP - (pos % TABSTOP);
            for (int i = 0; i < spaces; i++) {
                putchar('.');
                pos++;
            }
        } else {
            putchar(c);
            pos++;
            if (c == '\n') {
                pos = 0;
            }
        }
    }
    return 0;
}
