#include <stdio.h>
#define MAXLINE 1000

int getline_custom(char line[], int maxline);
void rtrim(char line[]);

int main(void) {
    char line[MAXLINE];
    int len;

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        rtrim(line);
        if (line[0] != '\0')
            printf("%s\n", line);
    }
    return 0;
}

int getline_custom(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void rtrim(char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; ++i)
        ;
    if (i == 0) return;

    i--;

    while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
        i--;
    s[i + 1] = '\0';
}
