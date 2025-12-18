#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
    int c, state;
    state = OUT;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                putchar('\n');
                state = OUT;
            }
        } else {
            putchar(c);
            state = IN;
        }
    }
return 0;
}

/* output
Hello   world
C programming
Hello
world
C
programming

c is a programming language
c
is
a
programming
language
*/
