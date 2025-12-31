/*Write a pointer version of the function strcat that we showed in Chapter 2
strcat(s,t) copies the string t to the end of s. */
#include <stdio.h>

void strcatp(char *s, char *t, int size) {
    int len = 0;

    if (s == NULL || t == NULL)
        return;

    while (*s) {
        s++;
        len++;
    }

    while (*t && len < size - 1) {
        *s++ = *t++;
        len++;
    }

    *s = '\0';
}

int main(void) {
    char s[100] = "Hello";
    char t[] = " World";

    strcatp(s, t, 100);
    printf("%s\n", s);

    char u[100] = "C programming";
    char v[] = " is powerful";

    strcatp(u, v, 100);
    printf("%s\n", u);

    char a[10] = "Hi";
    char b[] = "Everyone";

    strcatp(a, b, 10);
    printf("%s\n", a);

    char x[50] = "";
    char y[] = "Test";

    strcatp(x, y, 50);
    printf("%s\n", x);

    return 0;
}
/*output
Hello World
C programming is powerful
HiEveryon
Test
*/