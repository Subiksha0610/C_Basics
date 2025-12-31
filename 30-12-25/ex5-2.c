/* Write getfloat, the floating-point analog of getint. What type does 
getfloat return as its function value? */
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

int getfloat(float *pn) {
    int c, sign, seenDigit = 0;
    float power = 1.0;

    while (isspace(c = getch()))
        ;

    if (c == EOF)
        return EOF;

    if (!isdigit(c) && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int next = getch();
        if (next == EOF) {
            ungetch(c);
            return EOF;
        }
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            ungetch(c);
            return 0;
        }
        c = next;
    }

    *pn = 0.0;

    while (isdigit(c)) {
        seenDigit = 1;
        *pn = 10.0 * (*pn) + (c - '0');
        c = getch();
    }

    if (c == '.') {
        c = getch();
        while (isdigit(c)) {
            seenDigit = 1;
            *pn = 10.0 * (*pn) + (c - '0');
            power *= 10.0;
            c = getch();
        }
    }

    if (!seenDigit) {
        if (c != EOF)
            ungetch(c);
        return 0;
    }

    *pn = sign * (*pn) / power;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main(void) {
    int n;
    float val;
    while ((n = getfloat(&val)) != EOF) {
        if (n != 0)
            printf("Read float: %f\n", val);
    }
    return 0;
}

/*output
+.

-.

.5
Read float: 0.500000

5.
Read float: 5.000000

+12.34
Read float: 12.340000

-0.75
Read float: -0.750000

abc

*/