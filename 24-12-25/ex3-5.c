/*Write the function itob(n,s,b) that converts the integer n into a base b 
character representation in the string s. In particular, itob(n,s,16) formats s as a 
hexadecimal integer in s.*/
#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b) {
    if (b != 2 && b != 8 && b != 10 && b != 16) {
        printf("Invalid base. Only 2, 8, 10, 16 allowed.\n");
        s[0] = '\0';
        return;
    }

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
        s[j] ^= s[k];
        s[k] ^= s[j];
        s[j] ^= s[k];
    }
}

int main() {
    int n, b;
    char s[100];

    scanf("%d", &n);
    scanf("%d", &b);

    itob(n, s, b);

    if (s[0] != '\0')
        printf("%s\n", s);

    return 0;
}

/*output
Enter integer: -42
Enter base: 10
Converted: -42

Enter integer: 13
Enter base: 2
Converted: 1101

Enter integer: 255
Enter base: 16
Converted: FF

Enter integer: 64
Enter base: 8
Converted: 100
*/