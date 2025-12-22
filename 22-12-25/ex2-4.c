#include <ctype.h>
#include <stdio.h>

void squeeze(char s1[], char s2[]) {
    int i, j, k;
    for (i = j = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0' && tolower(s1[i]) != tolower(s2[k]); k++)
            ;
        if (s2[k] == '\0')
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

int main() {
    char s1[100], s2[100];
    printf("Enter first string: ");
    scanf("%99s", s1);
    printf("Enter second string: ");
    scanf("%99s", s2);
    squeeze(s1, s2);
    printf("Result: %s\n", s1);
    return 0;
}
