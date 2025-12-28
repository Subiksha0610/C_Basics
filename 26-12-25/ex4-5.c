/*Add access to library functions like sin, exp, and pow. See <math.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

int push(double f) {
    if (sp >= MAXVAL) {
        printf("Error: stack full\n");
        return 0;
    }
    val[sp++] = f;
    return 1;
}

int pop(double *out) {
    if (sp <= 0) {
        printf("Error: stack empty\n");
        return 0;
    }
    *out = val[--sp];
    return 1;
}

void print_top(void) {
    if (sp > 0)
        printf("Top: %g\n", val[sp - 1]);
    else
        printf("Stack empty\n");
}

void duplicate_top(void) {
    if (sp <= 0) {
        printf("Error: stack empty\n");
        return;
    }
    push(val[sp - 1]);
}

void swap_top(void) {
    if (sp < 2) {
        printf("Error: need two elements\n");
        return;
    }
    double t = val[sp - 1];
    val[sp - 1] = val[sp - 2];
    val[sp - 2] = t;
}

void clear_stack(void) {
    sp = 0;
    printf("Stack cleared\n");
}

int main(void) {
    char cmd[20];
    double a, b;

    printf("stack calculator\n");

    while (1) {
        printf("> ");
        if (scanf("%s", cmd) != 1)
            break;

        if (sscanf(cmd, "%lf", &a) == 1) {
            push(a);
            continue;
        }

        if (strcmp(cmd, "+") == 0) {
            if (pop(&b) && pop(&a)) push(a + b);
        }
        else if (strcmp(cmd, "-") == 0) {
            if (pop(&b) && pop(&a)) push(a - b);
        }
        else if (strcmp(cmd, "*") == 0) {
            if (pop(&b) && pop(&a)) push(a * b);
        }
        else if (strcmp(cmd, "/") == 0) {
            if (pop(&b) && pop(&a)) {
                if (b == 0)
                    printf("Error: division by zero\n");
                else
                    push(a / b);
            }
        }
        else if (strcmp(cmd, "%") == 0) {
            if (pop(&b) && pop(&a)) {
                if ((long)b == 0)
                    printf("Error: modulus by zero\n");
                else
                    push((long)a % (long)b);
            }
        }
        else if (strcmp(cmd, "sin") == 0) {
            if (pop(&a)) push(sin(a));
        }
        else if (strcmp(cmd, "exp") == 0) {
            if (pop(&a)) push(exp(a));
        }
        else if (strcmp(cmd, "pow") == 0) {
            if (pop(&b) && pop(&a)) push(pow(a, b));
        }
        else if (strcmp(cmd, "?") == 0) print_top();
        else if (strcmp(cmd, "d") == 0) duplicate_top();
        else if (strcmp(cmd, "s") == 0) swap_top();
        else if (strcmp(cmd, "c") == 0) clear_stack();
        else if (strcmp(cmd, "p") == 0) {
            if (pop(&a)) printf("Popped: %g\n", a);
        }
        else if (strcmp(cmd, "q") == 0) break;
        else printf("Unknown command\n");
    }

    return 0;
}
/*output
stack calculator
> 5
> 3
> +
> p
Popped: 8
> 10
> 4
> _
Unknown command
> 10
> 4
> -
> p
Popped: 6
> 10
> /
> 0

> 10
> 0
> /
Error: division by zero
> 8
> 0
> %
Error: modulus by zero
> +
Error: stack empty
> 5
> d
> ?
Top: 5

> 5
> d
> ?
Top: 5
> 3
> s
> p
Popped: 5
> 0
> sin
> p
Popped: 0
> 2
> exp
> p
Popped: 7.38906
> 2
> 3
> pow
> p
Popped: 8
> 9
> 4
> c
Stack cleared
> ?
Stack empty
> hello
Unknown command
> q
*/