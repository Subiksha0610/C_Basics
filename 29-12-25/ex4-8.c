/*Exercise 4-8. Suppose that there will never be more than one character of pushback. Modify 
getch and ungetch accordingly.*/
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
    if (buf != -1)
        return 0;
    buf = c;
    return 1;
}

int main(void) {
    int c;

    printf("Example 1: Pushback character 'A'\n");
    ungetch('A');

    while ((c = getch()) != EOF) {
        putchar(c);
    }

    printf("\nExample 2: User input \n");

    while ((c = getch()) != EOF) {
        putchar(c);
    }

    return 0;
}
