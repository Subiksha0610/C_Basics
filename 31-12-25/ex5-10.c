/*Write the program expr, which evaluates a reverse Polish expression from the 
command line, where each operator or operand is a separate argument. For example,  
   expr 2 3 4 + * 
evaluates 2 * (3+4).  */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXVAL 100
#define MAXLINE 1000

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else {
        printf("error: stack full\n");
        exit(1);
    }
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    printf("error: stack empty\n");
    exit(1);
}

int isnumber(char *s) {
    if (*s == '-' && *(s+1))
        s++;
    while (*s) {
        if (!isdigit(*s) && *s != '.')
            return 0;
        s++;
    }
    return 1;
}

int main(void) {
    char line[MAXLINE];
    char *token;
    double op2;

    printf("Enter the expression: ");
    fgets(line, MAXLINE, stdin);

    token = strtok(line, " \n");
    if (token == NULL) {
        printf("error: no expression\n");
        return 1;
    }

    while (token != NULL) {
        if (isnumber(token))
            push(atof(token));
        else if (strlen(token) == 1) {
            switch (*token) {
                case '+': push(pop() + pop()); break;
                case '*': push(pop() * pop()); break;
                case '-': op2 = pop(); push(pop() - op2); break;
                case '/':
                    op2 = pop();
                    if (op2 == 0) {
                        printf("error: zero divisor\n");
                        return 1;
                    }
                    push(pop() / op2);
                    break;
                default:
                    printf("error: invalid operator %s\n", token);
                    return 1;
            }
        } else {
            printf("error: invalid token %s\n", token);
            return 1;
        }
        token = strtok(NULL, " \n");
    }

    if (sp != 1) {
        printf("error: invalid expression\n");
        return 1;
    }

    printf("result = %.8g\n", pop());
    return 0;
}

/*output
Enter the expression: 8 7 +
result = 15

Enter the expression:
error: no expression

Enter the expression: 10 0 /
error: zero divisor

Enter the expression: 4 5 &
error: invalid operator &

Enter the expression: 3 4 5 +
error: invalid expression

Enter the expression: 5 1 + 6 8 - *
result = -12

Enter the expression: 5 1 2 + 4 * + 3 -
result = 14
*/