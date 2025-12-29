#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main(void) {
    int type;
    double op2;
    char s[100];
    int error = 0;

    while ((type = getop(s)) != EOF) {
        switch (type) {

        case NUMBER:
            push(atof(s));
            error = 0;
            break;

        case '+':
            push(pop() + pop());
            break;

        case '*':
            push(pop() * pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else {
                printf("error: zero divisor\n");
                clearstack();
                error = 1;
            }
            break;

        case '\n':
            if (!error)
                printf("\t%.8g\n", pop());
            error = 0;
            break;

        default:
            printf("error: unknown command %s\n", s);
            clearstack();
            error = 1;
            break;
        }
    }
    return 0;
}
