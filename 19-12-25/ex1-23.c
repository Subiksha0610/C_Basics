#include <stdio.h>

int main() {
    int c, prev = 0;
    int state = 0;  // 0=normal, 1=comment, 2=string, 3=char

    while ((c = getchar()) != EOF) {
        if (state == 0) {
            if (c == '/' && prev == '/') {
                putchar(prev);
                putchar(c);
                prev = 0;
            } else if (c == '*' && prev == '/') {
                state = 1;
                prev = 0;
                continue;
            } else {
                if (c == '"') state = 2;
                else if (c == '\'') state = 3;
                if (prev) putchar(prev);
                prev = c;
            }
        } else if (state == 1) {
            if (prev == '*' && c == '/') {
                state = 0;
                prev = 0;
                continue;
            }
            prev = c;
        } else if (state == 2) {
            putchar(c);
            if (c == '"' && prev != '\\') state = 0;
            prev = c;
        } else if (state == 3) {
            putchar(c);
            if (c == '\'' && prev != '\\') state = 0;
            prev = c;
        }
    }
    if (state == 0 && prev) putchar(prev);
    return 0;
}
