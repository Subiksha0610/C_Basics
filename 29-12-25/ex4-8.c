#include <stdio.h>

int buf = -1;

int getch(void) {
    int c;
    if (buf != -1) {
        c = buf;
        buf = -1;
        return c;
    }
    return getchar();
}

int ungetch(int c) {
    if (c == EOF)
        return 0;
    if (buf != -1)
        return 0;
    buf = c;
    return 1;
}

int main(void) {
    int c;

    while ((c = getch()) != EOF) {
        putchar(c);
    }
    return 0;
}
