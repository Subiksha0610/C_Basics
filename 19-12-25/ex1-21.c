/*Write a program entab that replaces strings of blanks by the minimum 
number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. 
When either a tab or a single blank would suffice to reach a tab stop, which should be given 
preference?  */
#include <stdio.h>

#define TABSTOP 8

int main(void) {
    int c, pos = 0, blanks = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            blanks++;
            pos++;
            if (pos % TABSTOP == 0) {
                putchar('\t');
                blanks = 0;
            }
        } else {
            while (blanks > 0) {
                putchar(' ');
                blanks--;
            }
            putchar(c);
            if (c == '\n') {
                pos = 0;
            } else if (c == '\t') {
                pos += TABSTOP - (pos % TABSTOP);
            } else {
                pos++;
            }
        }
    }
    return 0;
}
