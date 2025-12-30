#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}

int getint(int *pn) {
    int c, sign, next;

    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    if (!isdigit(c) && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        next = getch();
        if (next == EOF) {
            ungetch(c);
            return EOF;
        }
        if (!isdigit(next)) {
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    *pn = 0;
    while (isdigit(c)) {
        *pn = 10 * (*pn) + (c - '0');
        c = getch();
    }

    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main(void) {
    int n, val;
    while ((n = getint(&val)) != EOF) {
        if (n != 0)
            printf("Read integer: %d\n", val);
    }
    return 0;
}
