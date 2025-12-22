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
