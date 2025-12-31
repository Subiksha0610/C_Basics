#include <stdio.h>

#define MAXLINE 1000

int getline_ptr(char *s, int lim) {
    int c;
    char *start;

    if (s == NULL || lim <= 0)
        return 0;

    start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;

    if (c == '\n')
        *s++ = c;

    *s = '\0';

    if (c != '\n' && c != EOF) {
        while ((c = getchar()) != EOF && c != '\n')
            ;
    }

    if (c == EOF && s == start)
        return 0;

    return s - start;
}

int main(void) {
    char line[MAXLINE];
    int len;

    while ((len = getline_ptr(line, MAXLINE)) > 0)
        printf("Length: %d | Line: %s", len, line);

    return 0;
}
