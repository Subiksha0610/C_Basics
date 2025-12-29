/*Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input. 
Should ungets know about buf and bufp, or should it just use ungetch? */
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
    if (len > BUFSIZE - bufp)
        return 0;
    while (len > 0)
        ungetch(s[--len]);
    return 1;
}

int main(void) {
    char c;

    printf("Example 1: Push back string 'hello\\n'\n");
    ungets("hello\n");
    while ((c = getch()) != EOF)
        putchar(c);

    printf("Example 2: User input \n");
    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}
