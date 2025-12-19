#include <stdio.h>

int main() {
    int c;
    int paren = 0, bracket = 0, brace = 0;
    int state = 0;  // 0=normal, 1=comment, 2=string, 3=char
    int prev = 0;

    while ((c = getchar()) != EOF) {
        if (state == 0) {
            if (c == '/' && prev == '/') {
                prev = 0;
                putchar('/');
                putchar('/');
            } else if (c == '*' && prev == '/') {
                state = 1;
                prev = 0;
                continue;
            } else {
                if (c == '"') state = 2;
                else if (c == '\'') state = 3;
                else if (c == '(') paren++;
                else if (c == ')') paren--;
                else if (c == '[') bracket++;
                else if (c == ']') bracket--;
                else if (c == '{') brace++;
                else if (c == '}') brace--;
                prev = c;
            }
        } else if (state == 1) {
            if (prev == '*' && c == '/') {
                state = 0;
                prev = 0;
                continue;
            }
            prev = c;
        } else if (state == 2) {
            if (c == '"' && prev != '\\') state = 0;
            prev = c;
        } else if (state == 3) {
            if (c == '\'' && prev != '\\') state = 0;
            prev = c;
        }
    }

    if (paren != 0)
        printf("Unmatched parentheses: %d\n", paren);
    if (bracket != 0)
        printf("Unmatched brackets: %d\n", bracket);
    if (brace != 0)
        printf("Unmatched braces: %d\n", brace);

    return 0;
}
