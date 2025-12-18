#include <stdio.h>
#define MAXLINE 1000

int my_getline(char s[], int lim);
void reverse(char s[]);

int main(void) {
    char line[MAXLINE];
    int len;

    while ((len = my_getline(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s\n", line);
    }
    return 0;
}

int my_getline(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}

void reverse(char s[]) {
    int i = 0, j;
    char temp;
    while (s[i] != '\0') i++;
    if (i > 0 && s[i - 1] == '\n') i--; 
    j = i - 1;
    for (int k = 0; k < i / 2; k++) {
        temp = s[k];
        s[k] = s[j - k];
        s[j - k] = temp;
    }
}
