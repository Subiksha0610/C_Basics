#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    if (bufp > 0)
        return buf[--bufp];
    return getchar();
}

int ungetch(int c) {
    if (c == EOF)
        return 0;
    if (bufp >= BUFSIZE)
        return 0;
    buf[bufp++] = c;
    return 1;
}

int main(void) {
    int c;

    ungetch(EOF);
    ungetch('X');

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}
