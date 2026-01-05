/*Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations.  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void ungettoken(void);

int tokentype;
char token[MAXTOKEN];
char out[1000];

int need_parens(const char *s) {
    return strchr(s, '[') || strchr(s, '(');
}

int main(void) {
    while (gettoken() != EOF) {
        strcpy(out, token);
        while (gettoken() != '\n' && tokentype != EOF) {
            if (tokentype == PARENS || tokentype == BRACKETS) {
                strcat(out, token);
            } else if (tokentype == '*') {
                if (need_parens(out))
                    sprintf(out, "(*%s)", out);
                else
                    sprintf(out, "*%s", out);
            } else if (tokentype == NAME) {
                sprintf(out, "%s %s", token, out);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
    return 0;
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            tokentype = '(';
            token[0] = '(';
            token[1] = '\0';
        }
    } else if (c == '[') {
        *p++ = c;
        while ((*p++ = getchar()) != ']' && p - token < MAXTOKEN-1)
            ;
        *p = '\0';
        tokentype = BRACKETS;
    } else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        tokentype = NAME;
    } else {
        tokentype = c;
        token[0] = c;
        token[1] = '\0';
    }
    return tokentype;
}

void ungettoken(void) {
    for (int i = strlen(token)-1; i >= 0; i--)
        ungetc(token[i], stdin);
}
/*output
x *
*x

x () *
*x()

x [10] *
*x[10]

x * ()
*x()

x * *
**x

x * [5]
*x[5]
*/