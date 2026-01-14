/* Rewrite the postfix calculator of Chapter 4
the input and number conversion. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXVAL 100

double val[MAXVAL];
int sp = 0;

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int main(void) {
    char token[100];
    double op2;

    printf("Enter postfix expressions:\n");

    while (scanf("%99s", token) == 1) {

        if (isdigit(token[0]) ||
           (token[0] == '-' && isdigit(token[1])) ||
           (token[0] == '.' && isdigit(token[1]))) {

            char *end;
            double num = strtod(token, &end);
            if (*end == '\0')
                push(num);
            else
                printf("error: invalid number %s\n", token);

        } else if (strcmp(token, "+") == 0) {
            if (sp < 2) { printf("error: not enough operands\n"); continue; }
            push(pop() + pop());

        } else if (strcmp(token, "*") == 0) {
            if (sp < 2) { printf("error: not enough operands\n"); continue; }
            push(pop() * pop());

        } else if (strcmp(token, "-") == 0) {
            if (sp < 2) { printf("error: not enough operands\n"); continue; }
            op2 = pop();
            push(pop() - op2);

        } else if (strcmp(token, "/") == 0) {
            if (sp < 2) { printf("error: not enough operands\n"); continue; }
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else {
                printf("error: zero divisor\n");
                push(pop());
            }

        } else if (strcmp(token, "=") == 0) {
            if (sp == 1)
                printf("Result: %.8g\n", val[0]);
            else
                printf("error: too many operands\n");
            sp = 0;

        } else {
            printf("error: unknown command %s\n", token);
        }
    }
    return 0;
}
/*output
Enter postfix expressions:
3 4 +
=
Result: 7

.5 2 *
=
Result: 1

5
+ =
error: not enough operands


10 0 /
error: zero divisor
=


2 3 4 +
=
error: too many operands

2 3 &
=
error: too many operands

2 3 &
=
error: unknown command &
error: too many operands
*/