/*Extend atof to handle scientific notation of the form  
   123.45e-6 
where a floating-point number may be followed by e or E and an optionally signed exponent.*/
#include <stdio.h>
#include <ctype.h>

double atof_custom(char s[]) {
    double val = 0.0, power = 1.0;
    int i = 0, sign = 1, exp = 0, exp_sign = 1;

    while (isspace(s[i]))
        i++;

    if (s[i] == '-' || s[i] == '+') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    while (isdigit(s[i])) {
        val = val * 10 + (s[i] - '0');
        i++;
    }

    if (s[i] == '.') {
        i++;
        while (isdigit(s[i])) {
            val = val * 10 + (s[i] - '0');
            power *= 10;
            i++;
        }
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '-' || s[i] == '+') {
            exp_sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        while (isdigit(s[i])) {
            exp = exp * 10 + (s[i] - '0');
            i++;
        }
        while (exp-- > 0) {
            if (exp_sign == 1)
                val *= 10;
            else
                val /= 10;
        }
    }

    return val;
}

int get_line(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

#define MAXLINE 100

int main() {
    char line[MAXLINE];
    double sum = 0.0;

    printf("Enter numbers (Ctrl+D to stop):\n");
    while (get_line(line, MAXLINE) > 0) {
        sum += atof_custom(line);
        printf("%g\n", sum);
    }
    return 0;
}
