#include <ctype.h>
#include <stdio.h>
#include "calc.h"

int getop(char s[]) {
    static int buf = EOF;
    int c, i = 0;

    if (buf != EOF) {
        c = buf;
        buf = EOF;
    } else
        c = getchar();

    while (c == ' ' || c == '\t')
        c = getchar();

    if (c == EOF)
        return EOF;

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-') {
        int next = getchar();
        if (!isdigit(next) && next != '.') {
            buf = next;
            return '-';
        }
        s[++i] = next;
        c = next;
    }

    while (isdigit(c = getchar()))
     s[++i] = c;

    if (c == '.') {
        s[++i] = c;
        while (isdigit(c = getchar()))
            s[++i] = c;
    }

    s[++i] = '\0';
    buf = c;

    return NUMBER;
}