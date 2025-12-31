#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN   1000

int readlines(char lines[][MAXLEN], int maxlines);
void writelines(char lines[][MAXLEN], int nlines);
int getline_ptr(char *s, int lim);

int main(void) {
    char lines[MAXLINES][MAXLEN];
    int nlines;

    if ((nlines = readlines(lines, MAXLINES)) >= 0) {
        writelines(lines, nlines);
        return 0;
    } else {
        printf("error: too many lines\n");
        return 1;
    }
}

int readlines(char lines[][MAXLEN], int maxlines) {
    int len, nlines = 0;

    if (lines == NULL || maxlines <= 0)
        return -1;

    while ((len = getline_ptr(lines[nlines], MAXLEN)) > 0) {
        if (nlines >= maxlines)
            return -1;

        if (len > 0 && lines[nlines][len - 1] == '\n')
            lines[nlines][len - 1] = '\0';

        nlines++;
    }
    return nlines;
}

void writelines(char lines[][MAXLEN], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lines[i]);
}

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
