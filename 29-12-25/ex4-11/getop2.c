#include <ctype.h>
#include <stdio.h>
#include "calc.h"

int getop(char s[]) {
    static int lastc = ' ';
    int c, i = 0;

    c = (lastc != ' ') ? lastc : getchar();
    lastc = ' ';

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
            lastc = next;
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
    lastc = c;
    return NUMBER;
}
