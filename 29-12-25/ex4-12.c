/*Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert 
an integer into a string by calling a recursive routine.*/
#include <stdio.h>
#include <limits.h>

void itoa_recursive(int n, char s[], int *i) {
    if (n / 10)
        itoa_recursive(n / 10, s, i);
    s[(*i)++] = n % 10 + '0';
}

void itoa(int n, char s[]) {
    int i = 0;

    if (n == 0) {
        s[i++] = '0';
        s[i] = '\0';
        return;
    }

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

int main() {
    int n;
    char s[50];

    scanf("%d", &n);
    itoa(n, s);
    printf("%s\n", s);

    return 0;
}
/*output
0
0

12345
12345

-9876
-9876

2147483647
2147483647

-2147483648
-2147483648
*/