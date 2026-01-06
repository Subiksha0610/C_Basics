#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100

int getword(char *word, int lim) {
    int c, d;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;
    *w = '\0';

    if (c == '"') {
        while (--lim > 0 && (c = getchar()) != EOF) {
            *w++ = c;
            if (c == '\\') {
                *w++ = getchar();
                lim--;
            } else if (c == '"')
                break;
        }
        *w = '\0';
        return '"';
    }

    if (c == '\'') {
        while (--lim > 0 && (c = getchar()) != EOF) {
            *w++ = c;
            if (c == '\\') {
                *w++ = getchar();
                lim--;
            } else if (c == '\'')
                break;
        }
        *w = '\0';
        return '\'';
    }

    if (c == '/') {
        d = getchar();
        if (d == '/') {
            while ((c = getchar()) != EOF && c != '\n')
                ;
            return getword(word, lim);
        }
        if (d == '*') {
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        }
        ungetc(d, stdin);
        return '/';
    }

    if (c == '#') {
        while ((c = getchar()) != EOF) {
            if (c == '\n')
                break;
            if (c == '\\')
                getchar();
        }
        return '#';
    }

    if (!isalpha(c) && c != '_')
        return c;

    while (--lim > 0) {
        c = getchar();
        if (!isalnum(c) && c != '_') {
            ungetc(c, stdin);
            break;
        }
        *w++ = c;
    }

    *w = '\0';
    return word[0];
}

int main(void) {
    char word[MAXWORD];
    int type;

    while ((type = getword(word, MAXWORD)) != EOF)
        printf("Token: %s\n", word);

    return 0;
}
