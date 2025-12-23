/*Write a program detab that replaces tabs in the input with the proper number 
of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. 
Should n be a variable or a symbolic parameter? */

#include <stdio.h>

#define TABSTOP 8

int main(void) {
    int c, pos = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TABSTOP - (pos % TABSTOP);
            for (int i = 0; i < spaces; i++) {
                putchar('.');
                pos++;
            }
        } else {
            putchar(c);
            pos++;
            if (c == '\n') {
                pos = 0;
            }
        }
    }
    return 0;
}
/*output
hello           hi      from    ubuntu  ,
hello...............hi........from .....ubuntu....,
*/
