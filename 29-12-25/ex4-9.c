/*Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide 
what their properties ought to be if an EOF is pushed back, then implement your design.*/
#include <stdio.h>

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    if (bufp > 0)
        return buf[--bufp];
    return getchar();
}

int ungetch(int c) {
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
/*output
Enter text:
hello world
hello world

123
123

y
y
*/