#include <stdio.h>
#include <ctype.h>

int any(char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (tolower(s1[i]) == tolower(s2[j]))
                return i;
        }
    }
    return -1;
}

int main() {
    char s1[100], s2[100];
    printf("Enter first string: ");
    scanf("%99s", s1);
    printf("Enter second string: ");
    scanf("%99s", s2);
    int pos = any(s1, s2);
    printf("Result: %d\n", pos);
    return 0;
}
