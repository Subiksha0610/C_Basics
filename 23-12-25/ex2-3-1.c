#include <stdio.h>
#include <ctype.h>

int htoi(const char s[], int *valid) {
    int i = 0, value = 0, digit;
    int sign = 1;
    *valid = 1;

    
    while (isspace(s[i]))
        i++;

    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-')
            sign = -1;
        i++;
    }

    if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X')) {
        i += 2;
    }

    if (!isxdigit(s[i])) {
        *valid = 0;
        return 0;
    }

    for (; s[i] != '\0'; i++) {
        if (isdigit(s[i]))
            digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            digit = s[i] - 'A' + 10;
        else {
            *valid = 0;   
            return 0;
        }

        value = value * 16 + digit;
    }

    return sign * value;
}

int main() {
    char s[100];
    int valid, result;

    printf("Enter a hexadecimal number: ");
    scanf("%s", s);

    result = htoi(s, &valid);

    if (valid)
        printf("Decimal value = %d\n", result);
    else
        printf("Error: Enter a valid hexadecimal number\n");

    return 0;
}
