/*In a two's complement number representation, our version of itoa does not 
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why 
not. Modify it to print that value correctly, regardless of the machine on which it runs.  */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]) {
    unsigned int m;
    int i = 0, sign;

    sign = n;
    m = (sign < 0) ? -((unsigned int)n) : (unsigned int)n;

    do {
        s[i++] = m % 10 + '0';
        m /= 10;
    } while (m > 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';
    for (int j = 0, k = i-1; j < k; j++, k--) {
        char temp = s[j];
        s[j] = s[k];
        s[k] = temp;
    }
}

int main() {
    char buffer[50];
    int n;

    printf("Enter an integer: ");
    scanf("%d", &n);

    itoa(n, buffer);
    printf("String form: %s\n", buffer);

    return 0;
}
/*output
Enter an integer: -2147483648
String form: -2147483648
*/
