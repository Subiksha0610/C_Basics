/*Given the basic framework, it's straightforward to extend the calculator. Add 
the modulus (%) operator and provisions for negative numbers.  */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 200
int getline_ext(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

double evaluate(char line[], int *error) {
    char left[MAXLINE], right[MAXLINE], op;
    char *end;
    double a, b;

    if (sscanf(line, " %s %c %s", left, &op, right) == 3) {
        a = strtod(left, &end);
        if (*end != '\0') { *error = 1; return 0; }

        b = strtod(right, &end);
        if (*end != '\0') { *error = 1; return 0; }

        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/':
                if (b == 0) { *error = 2; return 0; }
                return a / b;
            case '%':
                if (b == 0) { *error = 3; return 0; }
                return fmod(a, b);
            default:
                *error = 4;
                return 0;
        }
    }

    a = strtod(line, &end);
    while (isspace(*end)) end++;

    if (*end == '\0')
        return a;

    *error = 1;
    return 0;
}

int main(void) {
    char line[MAXLINE];
    double result;
    int error;

    printf("Calculator\n");

    while (getline_ext(line, MAXLINE) > 0) {
        error = 0;
        result = evaluate(line, &error);

        if (error == 0)
            printf("Result = %g\n", result);
        else if (error == 1)
            printf("Error: Invalid input\n");
        else if (error == 2)
            printf("Error: Division by zero\n");
        else if (error == 3)
            printf("Error: Modulus by zero\n");
        else if (error == 4)
            printf("Error: Invalid operator\n");
    }
    return 0;
}
/*output
5 + 9
Result = 14
5 + 0
Result = 5
5
Result = 5
5 {+
Error: Invalid input
5 + k
Error: Invalid input
7.5 % 2
Result = 1.5
7 % 0
Error: Modulus by zero
2 / 0
Error: Division by zero
10 /4
Result = 2.5
*/