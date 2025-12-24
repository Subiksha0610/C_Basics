/* Write a version of itoa that accepts three arguments instead of two. The third 
argument is a minimum field width; the converted number must be padded with blanks on the 
left if necessary to make it wide enough. */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width) {
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
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = s[j];
        s[j] = s[k];
        s[k] = temp;
    }

    int len = strlen(s);
    if (len < width) {
        int pad = width - len;
        memmove(s + pad, s, len + 1);
        for (int j = 0; j < pad; j++)
            s[j] = ' ';
    }
}

int main() {
    int n, width;
    char s[100];
    printf("Enter integer: ");
    scanf("%d", &n);
    printf("Enter minimum width: ");
    scanf("%d", &width);
    itoa(n, s, width);
    printf("Converted: '%s'\n", s);
    return 0;
}
/*output

Enter integer: 42
Enter minimum width: 5
Converted: '   42'

Enter integer: -7
Enter minimum width: 3
Converted: ' -7'

Enter integer: 1234
Enter minimum width: 2
Converted: '1234'

Enter integer: 9
Enter minimum width: 4
Converted: '   9'
*/