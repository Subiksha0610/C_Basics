#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

int ungetch(int c) {
    if (bufp >= BUFSIZE)
        return 0;
    buf[bufp++] = c;
    return 1;
}

int ungets(const char *s) {
    int len;

    if (s == NULL)
        return 0;

    len = strlen(s);
    while (len > 0) {
        if (!ungetch(s[--len]))
            return 0;
    }
    return 1;
}

int main(void) {
    char c;

    ungets("hello\n");
    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}
