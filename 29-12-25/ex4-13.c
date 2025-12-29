/*Write a recursive version of the function reverse(s), which reverses the 
string s in place.*/
#include <stdio.h>
#include <string.h>

void reverse_rec(char s[], int i, int j) {
    if (i >= j) return;
    char t = s[i];
    s[i] = s[j];
    s[j] = t;
    reverse_rec(s, i + 1, j - 1);
}

void reverse(char s[]) {
    int n = strlen(s);
    if (n <= 1) return;
    reverse_rec(s, 0, n - 1);
}

int main() {
    char s[100];

    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    reverse(s);

    printf("%s\n", s);

    return 0;
}
/*output
a
a

abcd
dcba

abcde
edcba

hello world
dlrow olleh
*/
