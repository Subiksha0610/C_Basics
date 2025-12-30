#include <stdio.h>

void strncpy_p(char *s, char *t, int n) {
    if (s == NULL || t == NULL || n <= 0)
        return;

    while (n-- > 0 && (*s++ = *t++))
        ;

    while (n-- > 0)
        *s++ = '\0';
}

void strncat_p(char *s, char *t, int n) {
    if (s == NULL || t == NULL || n <= 0)
        return;

    while (*s)
        s++;

    while (n-- > 0 && *t)
        *s++ = *t++;

    *s = '\0';
}

int strncmp_p(char *s, char *t, int n) {
    if (s == NULL || t == NULL)
        return 0;

    while (n-- > 0) {
        if (*s != *t)
            return *s - *t;
        if (*s == '\0')
            return 0;
        s++;
        t++;
    }
    return 0;
}

int main(void) {
    char a[20];
    char b[20] = "hello";
    char c[20] = "world";

    strncpy_p(a, b, 3);
    a[3] = '\0';
    printf("%s\n", a);

    char d[40] = "foo";
    strncat_p(d, c, 3);
    printf("%s\n", d);

    printf("%d\n", strncmp_p("apple", "apricot", 3));
    printf("%d\n", strncmp_p("apple", "apricot", 5));

    printf("%d\n", strncmp_p("abc", "ab", 5));

    char e[10] = "";
    strncpy_p(e, "test", 0);
    printf("%s\n", e);

    return 0;
}
