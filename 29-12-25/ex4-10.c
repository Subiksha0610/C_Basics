#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000
#define MAXVAL 100
#define NUMBER '0'

double val[MAXVAL];
int sp = 0;

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack overflow\n");
}

int can_pop(int n) {
    if (sp < n) {
        printf("error: not enough operands\n");
        return 0;
    }
    return 1;
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    printf("error: stack empty\n");
    return 0.0;
}

int getline_custom(char line[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        line[i++] = c;
    if (c == '\n')
        line[i++] = c;
    line[i] = '\0';
    return i;
}

int getop(char line[], int *pos, char s[]) {
    int i = 0;
    while (line[*pos] == ' ' || line[*pos] == '\t')
        (*pos)++;

    if (line[*pos] == '\0')
        return '\0';

    s[i++] = line[*pos];

    if (!isdigit(line[*pos]) && line[*pos] != '.' && line[*pos] != '-') {
        (*pos)++;
        s[i] = '\0';
        return s[0];
    }

    if (line[*pos] == '-' && !isdigit(line[*pos + 1]) && line[*pos + 1] != '.') {
        (*pos)++;
        s[i] = '\0';
        return '-';
    }

    if (line[*pos] == '-' || isdigit(line[*pos]))
        s[i++] = line[++(*pos)];

    while (isdigit(line[*pos]))
        s[i++] = line[(*pos)++];

    if (line[*pos] == '.') {
        s[i++] = line[(*pos)++];
        while (isdigit(line[*pos]))
            s[i++] = line[(*pos)++];
    }

    s[i] = '\0';
    return NUMBER;
}

int main(void) {
    char line[MAXLINE];
    char token[MAXLINE];
    int type, pos;
    double op2;

    printf("Enter RPN expressions (Ctrl+D to quit)\n");

    while (getline_custom(line, MAXLINE) > 0) {
        pos = 0;
        sp = 0;

        while ((type = getop(line, &pos, token)) != '\0') {
            switch (type) {
                case NUMBER:
                    push(atof(token));
                    break;

                case '+':
                    if (can_pop(2))
                        push(pop() + pop());
                    break;

                case '*':
                    if (can_pop(2))
                        push(pop() * pop());
                    break;

                case '-':
                    if (can_pop(2)) {
                        op2 = pop();
                        push(pop() - op2);
                    }
                    break;

                case '/':
                    if (can_pop(2)) {
                        op2 = pop();
                        if (op2 != 0.0)
                            push(pop() / op2);
                        else
                            printf("error: division by zero\n");
                    }
                    break;

                case '\n':
                    break;

                default:
                    printf("error: invalid token '%s'\n", token);
                    break;
            }
        }

        if (sp == 1)
            printf("Result: %.8g\n", pop());
        else if (sp > 1)
            printf("error: too many operands left on stack\n");
    }

    return 0;
}
