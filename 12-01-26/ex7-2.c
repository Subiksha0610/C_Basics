/*Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a 
minimum, it should print non-graphic characters in octal or hexadecimal according to local 
custom, and break long text lines.  */
#include <stdio.h>
#include <ctype.h>

#define MAXCOL 80
#define TABSTOP 8

int main(void) {
    int c;
    int col = 0;

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            putchar('\n');
            col = 0;
        }
        else if (c == '\t') {
            int spaces = TABSTOP - (col % TABSTOP);
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
            }
            col += spaces;
        }
        else if (c == '\b') {
            if (col > 0)
                col--;
            printf("\\%03o", c);
            col += 4;
        }
        else if (isprint(c)) {
            putchar(c);
            col++;
        }
        else {
            if (col + 4 > MAXCOL) {
                putchar('\n');
                col = 0;
            }
            printf("\\%03o", c);
            col += 4;
        }

        if (col >= MAXCOL) {
            putchar('\n');
            col = 0;
        }
    }
    return 0;
}
/*output
Hello
World
Hello
World

A       B
A       B

A^Gb
A\007b


ab
ab


aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa


hi ^A there
hi \001 there
*/