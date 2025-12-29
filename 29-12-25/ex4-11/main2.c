/*Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal 
static variable.  */
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
            break;

        case '+':
    if (stacksize() < 2) {
        printf("error: stack empty\n");
        clearstack();
        error = 1;
    } else
        push(pop() + pop());
    break;

case '-':
    if (stacksize() < 2) {
        printf("error: stack empty\n");
        clearstack();
        error = 1;
    } else {
        op2 = pop();
        push(pop() - op2);
    }
    break;
    case '*':
    if (stacksize() < 2) {
        printf("error: stack empty\n");
        clearstack();
        error = 1;
    } else
        push(pop() * pop());
    break;

case '/':
    if (stacksize() < 2) {
        printf("error: stack empty\n");
        clearstack();
        error = 1;
    } else {
        op2 = pop();
        if (op2 != 0.0)
            push(pop() / op2);
        else {
            printf("error: zero divisor\n");
            clearstack();
            error = 1;
        }
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
/*output
3 4 +
        7
10 2 -
        8
-5 3 *
        -15
5 0 /
error: zero divisor
7 +
error: stack empty
5 0 /
error: zero divisor
9 - 8
error: stack empty
*/