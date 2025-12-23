#include <stdio.h>

#define NORMAL 0
#define SL_COMMENT 1
#define ML_COMMENT 2
#define STRING 3
#define CHAR 4

int main() {
    int c, next;
    int state = NORMAL;

    while ((c = getchar()) != EOF) {

        if (state == NORMAL) {
            if (c == '/') {
                next = getchar();
                if (next == '/') {
                    state = SL_COMMENT;
                } else if (next == '*') {
                    state = ML_COMMENT;
                } else {
                    putchar(c);
                    ungetc(next, stdin);
                }
            }
            else if (c == '"') {
                putchar(c);
                state = STRING;
            }
            else if (c == '\'') {
                putchar(c);
                state = CHAR;
            }
            else {
                putchar(c);
            }
        }

        else if (state == SL_COMMENT) {
            if (c == '\n') {
                putchar('\n');
                state = NORMAL;
            }
        }

        else if (state == ML_COMMENT) {
            if (c == '*') {
                next = getchar();
                if (next == '/') {
                    state = NORMAL;
                } else {
                    ungetc(next, stdin);
                }
            }
        }

        else if (state == STRING) {
            putchar(c);
            if (c == '\\') {          
                putchar(getchar());
            }
            else if (c == '"') {
                state = NORMAL;
            }
        }

        else if (state == CHAR) {
            putchar(c);
            if (c == '\\') {         
                putchar(getchar());
            }
            else if (c == '\'') {
                state = NORMAL;
            }
        }
    }
    return 0;
}
