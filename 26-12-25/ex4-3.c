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

int is_valid_number(const char *s) {
    int dot = 0, digit = 0;
    if (*s == '+' || *s == '-') s++;
    while (*s) {
        if (*s == '.') {
            if (dot) return 0;
            dot = 1;
        } else if (isdigit(*s)) {
            digit = 1;
        } else if (!isspace(*s)) {
            return 0;
        }
        s++;
    }
    return digit;
}

double atof_ext(char s[]) {
    return strtod(s, NULL);
}

double evaluate(char line[], int *error) {
    char left[MAXLINE], right[MAXLINE], op;
    double a, b;

    if (sscanf(line, " %199s %c %199s", left, &op, right) == 3) {
        if (!is_valid_number(left) || !is_valid_number(right)) {
            *error = 1;
            return 0;
        }

        a = atof_ext(left);
        b = atof_ext(right);

        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/':
                if (b == 0) {
                    *error = 2;
                    return 0;
                }
                return a / b;
            case '%':
                if (b == 0) {
                    *error = 3;
                    return 0;
                }
                return fmod(a, b);
            default:
                *error = 4;
                return 0;
        }
    }

    if (is_valid_number(line))
        return atof_ext(line);

    *error = 1;
    return 0;
}

int main() {
    char line[MAXLINE];
    double result;
    int error;

    printf("Calculator ready. Ctrl+D to exit.\n");

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
