/*Exercise 5-20. Expand dcl to handle declarations with function argument types, qualifiers 
like const, and so on. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void dcl(void);
void dirdcl(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int isqualifier(const char *s) {
    return strcmp(s,"const")==0 || strcmp(s,"volatile")==0;
}

int istype(const char *s) {
    return strcmp(s,"int")==0 || strcmp(s,"char")==0 ||
           strcmp(s,"void")==0 || strcmp(s,"float")==0 ||
           strcmp(s,"double")==0;
}

int main(void) {
    while (gettoken() != EOF) {
        datatype[0] = '\0';
        do {
            if (isqualifier(token) || istype(token)) {
                if (datatype[0]) strcat(datatype, " ");
                strcat(datatype, token);
            }
            gettoken();
        } while (isqualifier(token) || istype(token));

        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

void dcl(void) {
    int ns = 0;
    while (tokentype == '*') {
        ns++;
        gettoken();
        while (isqualifier(token)) {
            strcat(out, " ");
            strcat(out, token);
            gettoken();
        }
    }
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void) {
    if (tokentype == '(') {
        gettoken();
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
        else
            gettoken();
    } else if (tokentype == NAME) {
        strcpy(name, token);
        gettoken();
    } else {
        printf("error: expected name or (dcl)\n");
    }

    while (tokentype == PARENS || tokentype == BRACKETS) {
        if (tokentype == PARENS) {
            strcat(out, " function");
            if (strcmp(token,"()") != 0) {
                strcat(out, " taking ");
                strcat(out, token);
            }
            strcat(out, " returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
        gettoken();
    }
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        int d = getchar();
        if (d == ')') {
            strcpy(token,"()");
            tokentype = PARENS;
        } else {
            *p++ = '(';
            ungetc(d,stdin);
            while ((c=getchar())!=')' && c!=EOF && p-token<MAXTOKEN-1)
                *p++ = c;
            *p++ = ')';
            *p = '\0';
            tokentype = PARENS;
        }
        return tokentype;
    }

    if (c == '[') {
        *p++ = '[';
        while ((c=getchar())!=']' && c!=EOF && p-token<MAXTOKEN-1)
            *p++ = c;
        *p++ = ']';
        *p = '\0';
        tokentype = BRACKETS;
        return tokentype;
    }

    if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c=getchar()))
            *p++ = c;
        *p = '\0';
        ungetc(c,stdin);
        tokentype = NAME;
        return tokentype;
    }

    tokentype = c;
    token[0] = c;
    token[1] = '\0';
    return tokentype;
}
/*output
const volatile int *p
p:  pointer to const volatile int

int * const p
p:  const pointer to int

int f(int, const char *)
f:  function taking (int, const char *) returning int

int (*fp)(int *)
error: expected name or (dcl)
f:  function taking (*fp) returning function taking (int *) returning int

char (*a[5])(void)
error: expected name or (dcl)
f:  function taking (*a[5]) returning function taking (void) returning char

*/