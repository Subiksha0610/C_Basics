/*Write a program to ``fold'' long input lines into two or more shorter lines after 
the last non-blank character that occurs before the n-th column of input. Make sure your 
program does something intelligent with very long lines, and if there are no blanks or tabs 
before the specified column.*/

#include <stdio.h>
#define MAXCOL 20

int main(void) {
    int c, pos;
    char line[MAXCOL];

    pos = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line[pos] = c;
            pos++;
            for (int i = 0; i < pos; i++)
                putchar(line[i]);
            pos = 0;
        } else {
            line[pos] = c;
            pos++;
            if (pos >= MAXCOL) {
                int breakpos = pos - 1;
                while (breakpos > 0 && line[breakpos] != ' ' && line[breakpos] != '\t')
                    breakpos--;
                if (breakpos == 0) breakpos = pos;
                for (int i = 0; i < breakpos; i++)
                    putchar(line[i]);
                putchar('\n');
                pos = pos - breakpos;
                for (int i = 0; i < pos; i++)
                    line[i] = line[breakpos + i];
            }
        }
    }
    return 0;
}

/* output
hi, i am subiksha from karaikudi.. i'm currently doing my final year computer science and engineering
hi, i am subiksha
 from karaikudi..
 i'm currently
 doing my final
 year computer
 science and
 engineering
*/
