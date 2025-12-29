/*Exercise 4-6. Add commands for handling variables. (It's easy to provide twenty-six variables 
with single-letter names.) Add a variable for the most recently printed value. */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NUMVARS 26
#define MAXLINE 100

int main(void) {
    double vars[NUMVARS] = {0};
    double last = 0;
    char line[MAXLINE];

    while (1) {
        printf("> ");
        if (!fgets(line, MAXLINE, stdin))
            break;

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "quit") == 0)
            break;

        if (strncmp(line, "print", 5) == 0) {
            char *p = line + 5;
            while (isspace(*p)) p++;

            if (strcmp(p, "last") == 0) {
                printf("last = %g\n", last);
            } else if (isalpha(*p) && p[1] == '\0') {
                int idx = tolower(*p) - 'a';
                if (idx >= 0 && idx < NUMVARS) {
                    printf("%c = %g\n", *p, vars[idx]);
                    last = vars[idx];
                } else {
                    printf("Invalid variable\n");
                }
            } else {
                printf("Invalid print command\n");
            }
            continue;
        }

        char var;
        char rhs[50];
        double value;

        if (sscanf(line, " %c = %49s", &var, rhs) == 2 && isalpha(var)) {
            int idx = tolower(var) - 'a';
            if (idx < 0 || idx >= NUMVARS) {
                printf("Invalid variable\n");
                continue;
            }

            if (strcmp(rhs, "last") == 0) {
                vars[idx] = last;
                last = vars[idx];
            } else if (isalpha(rhs[0]) && rhs[1] == '\0') {
                int r = tolower(rhs[0]) - 'a';
                if (r >= 0 && r < NUMVARS) {
                    vars[idx] = vars[r];
                    last = vars[idx];
                } else {
                    printf("Invalid RHS variable\n");
                }
            } else if (sscanf(rhs, "%lf", &value) == 1) {
                vars[idx] = value;
                last = value;
            } else {
                printf("Invalid assignment\n");
            }
            continue;
        }

        printf("Unrecognized command\n");
    }

    return 0;
}
/*output
> a = 10
> print last
last = 10
> print a
a = 10
> b = a
> print b
b = 10
> c = last
> print c
c = 10
> d = 12abc
> a =
Unrecognized command
> 1 = 5
Unrecognized command
> print z
z = 0
> quit
*/