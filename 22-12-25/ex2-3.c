/*Write a function htoi(s), which converts a string of hexadecimal digits 
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 
through 9, a through f, and A through F. */
#include <stdio.h>
#include <ctype.h>

int htoi(char s[]) {
    int i = 0, n = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
    for (; s[i] != '\0'; i++) {
        if (isdigit(s[i]))
            n = 16 * n + (s[i] - '0');
        else if (s[i] >= 'a' && s[i] <= 'f')
            n = 16 * n + (s[i] - 'a' + 10);
        else if (s[i] >= 'A' && s[i] <= 'F')
            n = 16 * n + (s[i] - 'A' + 10);
    }
    return n;
}

int main() {
    char hex[100]; 
	printf("Enter a hexadecimal number: ");
	scanf("%99s", hex);
	printf("Decimal value: %d\n", htoi(hex)); 
	return 0; 
}

/* output
Enter a hexadecimal number: 0x213AB
Decimal value: 136107

Enter a hexadecimal number: Oxa1
Decimal value: 161

Enter a hexadecimal number: 0xa
Decimal value: 10
*/
