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
        double value;
        char rhs[50];

        if (sscanf(line, " %c = %49s", &var, rhs) == 2 && isalpha(var)) {
            var = tolower(var);
            int idx = var - 'a';

            if (strcmp(rhs, "last") == 0) {
                vars[idx] = last;
                last = vars[idx];
            }
            else if (isalpha(rhs[0]) && rhs[1] == '\0') {
                int r = tolower(rhs[0]) - 'a';
                if (r >= 0 && r < NUMVARS) {
                    vars[idx] = vars[r];
                    last = vars[idx];
                } else {
                    printf("Invalid variable on RHS\n");
                }
            }
            else if (sscanf(rhs, "%lf", &value) == 1) {
                vars[idx] = value;
                last = value;
            }
            else {
                printf("Invalid assignment\n");
            }
            continue;
        }

        printf("Unrecognized command\n");
    }

    return 0;
}
