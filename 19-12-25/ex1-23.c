/*Write a program to remove all comments from a C program. Don't forget to 
handle quoted strings and character constants properly. C comments don't nest.  */
#include <stdio.h>

int main() {
    int c, prev = 0;
    int state = 0;  // 0=normal, 1=comment, 2=string, 3=char

    while ((c = getchar()) != EOF) {

        if (state == 0) {
            if (prev == '/' && c == '/') {
                while ((c = getchar()) != '\n' && c != EOF); 
                prev = 0;
                if (c == '\n')
                    putchar('\n');
                continue;
            }
            else if (prev == '/' && c == '*') {
                state = 1; 
                prev = 0;
                continue;
            }
            else if (c == '"') {
                if (prev) putchar(prev);
                putchar(c);
                state = 2;
                prev = 0;
                continue;
            }
            else if (c == '\'') {
                if (prev) putchar(prev);
                putchar(c);
                state = 3;
                prev = 0;
                continue;
            }
            if (prev) putchar(prev);
            prev = c;
        }
        else if (state == 1) {  
            if (prev == '*' && c == '/') {
                state = 0;  
                prev = 0;
            } else {
                prev = c;  
            }
        }
        else if (state == 2) {  
            putchar(c);
            if (c == '"' && prev != '\\')
                state = 0;
            prev = c;
        }
        else if (state == 3) {  
            putchar(c);
            if (c == '\'' && prev != '\\')
                state = 0;
            prev = c;
        }
    }
    if (state == 0 && prev) putchar(prev);  
    return 0;
}


//output
//Hello /* remove this */ World
//Hello  World

//printf("This /* is not */ a comment");
//printf(This /* is not */ a comment"");
