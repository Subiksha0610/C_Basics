#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b) {
    unsigned int m;
    int i = 0, sign;

    sign = n;
    m = (sign < 0) ? -((unsigned int)n) : (unsigned int)n;

    do {
        int digit = m % b;
        s[i++] = (digit < 10) ? digit + '0' : digit - 10 + 'A';
        m /= b;
    } while (m > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = s[j];
        s[j] = s[k];
        s[k] = temp;
    }
}

int main() {
    int n, b;
    char s[100];
    printf("Enter integer: ");
    scanf("%d", &n);
    printf("Enter base: ");
    scanf("%d", &b);
    itob(n, s, b);
    printf("Converted: %s\n", s);
    return 0;
}
