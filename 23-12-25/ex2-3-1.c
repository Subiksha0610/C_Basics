/*Write a function htoi(s), which converts a string of hexadecimal digits 
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 
through 9, a through f, and A through F. */
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

/*output
Enter a hexadecimal number: -1A
Decimal value = -26

Enter a hexadecimal number: BF0x1
Error: Enter a valid hexadecimal number

Enter a hexadecimal number: xyz
Error: Enter a valid hexadecimal number

Enter a hexadecimal number: "0x1f"
Error: Enter a valid hexadecimal number

Enter a hexadecimal number: 0x1f
Decimal value = 31

Enter a hexadecimal number:       0x1f
Decimal value = 31

Enter a hexadecimal number: 10x2
Error: Enter a valid hexadecimal number

Enter a hexadecimal number: G12
Error: Enter a valid hexadecimal number

Enter a hexadecimal number: 12G4
Error: Enter a valid hexadecimal number

Enter a hexadecimal number: ffffff
Decimal value = 16777215

Enter a hexadecimal number: ffffffff
Decimal value = -1

Enter a hexadecimal number: f
Decimal value = 15

Enter a hexadecimal number: aF
Decimal value = 175

Enter a hexadecimal number: 1A
Decimal value = 26

Enter a hexadecimal number: 0x
Error: Enter a valid hexadecimal number

Enter a hexadecimal number:

Error: Enter a valid hexadecimal number
*/
