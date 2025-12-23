/*Write a program to remove all comments from a C program. Don't forget to 
handle quoted strings and character constants properly. C comments don't nest.  */
#include <stdio.h>

int main() {
    int c, next;
    int state = 0; // 0=normal, 1=comment, 2=string, 3=char

    while ((c = getchar()) != EOF) {
        if (state == 0) {

            if (c == '/') {
                next = getchar();
                if (next == '/') {
                    while ((c = getchar()) != '\n' && c != EOF);
                    if (c == '\n') putchar('\n');
                    continue;
                } else if (next == '*') {
                    state = 1;
                    continue;
                } else {
                    putchar(c);
                    c = next;
                }
            }

            if (c == '"') { putchar(c); state = 2; continue; }
            if (c == '\'') { putchar(c); state = 3; continue; }

            putchar(c);
        }


        else if (state == 1) {
            if (c == '*') {
                next = getchar();
                if (next == '/') { state = 0; continue; }
                else c = next;
            }
 }


        else if (state == 2) {
            putchar(c);
            if (c == '\\') {
                c = getchar();
                putchar(c);
            } else if (c == '"') state = 0;
        }


        else if (state == 3) {
            putchar(c);
            if (c == '\\') {
                c = getchar();
                putchar(c);
            } else if (c == '\'') state = 0;
        }
    }

    return 0;
}

//output
//Hello /* remove this */ World
//Hello  World

//printf("This /* is not */ a comment");
//printf(This /* is not */ a comment"");
