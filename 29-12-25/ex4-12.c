#include <limits.h>

void itoa_recursive(int n, char s[], int *i) {
    if (n / 10)
        itoa_recursive(n / 10, s, i);
    s[(*i)++] = n % 10 + '0';
}

void itoa(int n, char s[]) {
    int i = 0;
    if (n < 0) {
        s[i++] = '-';
        if (n == INT_MIN) {
            itoa_recursive(-(n / 10), s, &i);
            s[i++] = -(n % 10) + '0';
            s[i] = '\0';
            return;
        }
        n = -n;
    }
    itoa_recursive(n, s, &i);
    s[i] = '\0';
}
