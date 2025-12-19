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
