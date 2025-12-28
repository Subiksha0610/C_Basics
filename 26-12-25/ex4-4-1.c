/*Add the commands to print the top elements of the stack without popping, to 
duplicate it, and to swap the top two elements. Add a command to clear the stack. */
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
        printf("Error: stack full\n");
}

int pop(double *out) {
    if (sp > 0) {
        *out = val[--sp];
        return 1;
    }
    printf("Error: stack empty\n");
    return 0;
}

void print_top(void) {
    if (sp > 0)
        printf("Top: %g\n", val[sp - 1]);
    else
        printf("Error: stack empty\n");
}

void duplicate_top(void) {
    if (sp == 0) {
        printf("Error: stack empty\n");
        return;
    }
    if (sp == MAXVAL) {
        printf("Error: stack full\n");
        return;
    }
    push(val[sp - 1]);
}

void swap_top(void) {
    if (sp < 2) {
        printf("Error: need two elements to swap\n");
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

void flush_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main(void) {
    char cmd;
    double num, out;

    printf("Stack commands:\n");
    printf("number  push\n");
    printf("?       print top\n");
    printf("d       duplicate top\n");
    printf("s       swap top two\n");
    printf("c       clear stack\n");
    printf("p       pop\n");
    printf("q       quit\n");

    while (1) {
        printf("> ");

        if (scanf("%lf", &num) == 1) {
            push(num);
            continue;
        }

        if (scanf(" %c", &cmd) != 1)
            break;

        switch (cmd) {
            case '?': print_top(); break;
            case 'd': duplicate_top(); break;
            case 's': swap_top(); break;
            case 'c': clear_stack(); break;
            case 'p':
                if (pop(&out))
                    printf("Popped: %g\n", out);
                break;
            case 'q':
                return 0;
            default:
                printf("Error: unknown command '%c'\n", cmd);
        }

        flush_line();
    }
    return 0;
}
/*output
Stack commands:
number  push
?       print top
d       duplicate top
s       swap top two
c       clear stack
p       pop
q       quit
> ?
Error: stack empty
> 7
> 6
> 5
> 4
> ?
Top: 4
> d
> s
> ?
Top: 4
> p
Popped: 4
> ?
Top: 4
> p
Popped: 4
> ?
Top: 5
> s
> ?
Top: 6
> d
> p
Popped: 6
> ?
Top: 6
> c
Stack cleared
> ?
Error: stack empty
*/