/*Exercise 5-18. Make dcl recover from input errors.  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void dcl(void);
void dirdcl(void);
void skipline(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
int errorflag = 0;

int main(void) {
    while (gettoken() != EOF) {
        errorflag = 0;
        strcpy(datatype, token);
        out[0] = '\0';
        name[0] = '\0';
        dcl();
        if (tokentype != '\n' && !errorflag)
            printf("syntax error\n");
        if (!errorflag)
            printf("%s: %s %s\n", name, out, datatype);
        skipline();
    }
    return 0;
}

void dcl(void) {
    int ns = 0;
    while (tokentype == '*') {
        ns++;
        gettoken();
    }
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void) {
    if (tokentype == '(') {
        gettoken();
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            errorflag = 1;
        } else
            gettoken();
    } else if (tokentype == NAME) {
        strcpy(name, token);
        gettoken();
    } else {
        printf("error: expected name or (dcl)\n");
        errorflag = 1;
        return;
    }

    while (tokentype == PARENS || tokentype == BRACKETS) {
        if (tokentype == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
        gettoken();
    }
}

int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            tokentype = PARENS;
        } else {
            ungetch(c);
            tokentype = '(';
        }
    } else if (c == '[') {
        *p++ = c;
        while ((c = getch()) != ']' && c != '\n' && c != EOF && p - token < MAXTOKEN-1)
            *p++ = c;
        if (c != ']') {
            printf("error: missing ]\n");
            errorflag = 1;
            tokentype = '\n';
        } else {
            *p++ = ']';
            *p = '\0';
            tokentype = BRACKETS;
        }
    } else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getch()))
            *p++ = c;
        *p = '\0';
        ungetch(c);
        tokentype = NAME;
    } else {
        tokentype = c;
        token[0] = c;
        token[1] = '\0';
    }
    return tokentype;
}

void skipline(void) {
    while (tokentype != '\n' && tokentype != EOF)
        gettoken();
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
}
/*output
int (*x
syntax error
int:  int

error: expected name or (dcl)

int a[10
syntax error
int:  int
error: missing ]

int * ) x
syntax error
int:  int

int a[10
char *psyntax error
int:  int
error: missing ]

syntax error
char:  char

error: expected name or (dcl)
char (*fp)()
syntax error
char:  char
*/