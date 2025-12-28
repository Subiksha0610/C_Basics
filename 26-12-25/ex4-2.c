/*Extend atof to handle scientific notation of the form  
   123.45e-6 
where a floating-point number may be followed by e or E and an optionally signed exponent.*/
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

int get_line(char s[], int lim);
int safe_atof(char s[], double *result);

int main(void) {
    char line[MAXLINE];
    double sum = 0.0, value;

    printf("Enter numbers:\n");

    while (get_line(line, MAXLINE) > 0) {
        if (safe_atof(line, &value)) {
            sum += value;
            printf("\t%g\n", sum);
        } else {
            printf("Invalid input ignored\n");
        }
    }
    return 0;
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

int safe_atof(char s[], double *result) {
    int i = 0, sign = 1, exp_sign = 1, exp = 0;
    double val = 0.0, power = 1.0;
    int digits = 0;

    while (isspace(s[i])) i++;

    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') sign = -1;
        i++;
    }

    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        i++;
        digits++;
    }

    if (s[i] == '.') {
        i++;
        while (isdigit(s[i])) {
            val = 10.0 * val + (s[i] - '0');
            power *= 10.0;
            i++;
            digits++;
        }
    }

    if (digits == 0)
        return 0;

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        if (s[i] == '+' || s[i] == '-') {
            if (s[i] == '-') exp_sign = -1;
            i++;
        }

        if (!isdigit(s[i]))
            return 0;

        while (isdigit(s[i])) {
            exp = 10 * exp + (s[i] - '0');
            i++;
        }

        while (exp-- > 0) {
            if (exp_sign == 1)
                val *= 10;
            else
                val /= 10;
        }
    }

    while (isspace(s[i])) i++;

    if (s[i] != '\0' && s[i] != '\n')
        return 0;

    *result = val;
    return 1;
}

/*output
Enter numbers (Ctrl+D to end):
abc
Invalid input ignored
10
        10
3.5
        13.5
2.5
        16
-4
        12
1e2
        112
5E-1
        112.5
.
Invalid input ignored
+
Invalid input ignored
12e
Invalid input ignored
12abc
Invalid input ignored
2.2.1
Invalid input ignored
e10
Invalid input ignored

Invalid input ignored
1000000000
        1e+09
1000000
        1.001e+09
abc
Invalid input ignored
3.2
        1.001e+09
2e-9
        1.001e+09
10
        1.001e+09
subiksha@DESKTOP-CBQDRR5:~$ ./ex4-2
Enter numbers (Ctrl+D to end):
10
        10
13.2
        23.2
*/