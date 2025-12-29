#include <stdio.h>
#include <string.h>

void reverse(char s[], int i, int j) {
    if (i >= j) return;
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    reverse(s, i+1, j-1);
}

int main() {
    char s1[] = "";
    char s2[] = "a";
    char s3[] = "abcd";
    char s4[] = "abcde";
    char s5[] = "hello world!";
    reverse(s1, 0, strlen(s1)-1);
    reverse(s2, 0, strlen(s2)-1);
    reverse(s3, 0, strlen(s3)-1);
    reverse(s4, 0, strlen(s4)-1);
    reverse(s5, 0, strlen(s5)-1);
    printf("Empty -> '%s'\n", s1);
    printf("Single -> '%s'\n", s2);
    printf("Even -> '%s'\n", s3);
    printf("Odd -> '%s'\n", s4);
    printf("Special -> '%s'\n", s5);
    return 0;
}
