#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]) {
    int i, j;
    for (i = j = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0' &&
            ((isalnum(s1[i-1]) && isalnum(s1[i+1])) &&
             (s1[i-1] < s1[i+1]))) {
            char start = s1[i-1] + 1;
            char end = s1[i+1];
            while (start < end)
                s2[j++] = start++;
        } else {
            s2[j++] = s1[i];
        }
    }
    s2[j] = '\0';
}

int main() {
    char s1[100], s2[500];
    printf("Enter shorthand string: ");
    fgets(s1, sizeof(s1), stdin);
    expand(s1, s2);
    printf("%s", s2);
    return 0;
}

