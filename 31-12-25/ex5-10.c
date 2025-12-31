#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

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

int isnumber(char *s) {
    if (*s == '+' || *s == '-')
        s++;
    int seen = 0;
    while (isdigit(*s)) {
        seen = 1;
        s++;
    }
    if (*s == '.') {
        s++;
        while (isdigit(*s)) {
            seen = 1;
            s++;
        }
    }
    return seen && *s == '\0';
}

int main(int argc, char *argv[]) {
    double op2;

    if (argc <= 1) {
        printf("error: no expression\n");
        return 1;
    }

    while (--argc > 0) {
        argv++;

        if (isnumber(*argv)) {
            push(atof(*argv));
        }
        else if (**argv == '+' && (*argv)[1] == '\0') {
            if (sp < 2) { printf("error: not enough operands\n"); return 1; }
            push(pop() + pop());
        }
        else if (**argv == '*' && (*argv)[1] == '\0') {
            if (sp < 2) { printf("error: not enough operands\n"); return 1; }
            push(pop() * pop());
        }
        else if (**argv == '-' && (*argv)[1] == '\0') {
            if (sp < 2) { printf("error: not enough operands\n"); return 1; }
            op2 = pop();
            push(pop() - op2);
        }
        else if (**argv == '/' && (*argv)[1] == '\0') {
            if (sp < 2) { printf("error: not enough operands\n"); return 1; }
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else {
                printf("error: zero divisor\n");
                return 1;
            }
        }
        else {
            printf("error: invalid operand %s\n", *argv);
            return 1;
        }
    }

    if (sp != 1) {
        printf("error: invalid expression\n");
        return 1;
    }

    printf("result = %.8g\n", pop());
    return 0;
}
