#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAXLINE];
    char *pattern;
    int lineno;
    int i;
    int found = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s pattern [file ...]\n", argv[0]);
        return 1;
    }

    pattern = argv[1];

    if (*pattern == '\0') {
        fprintf(stderr, "Error: empty pattern\n");
        return 1;
    }

    if (argc == 2) {
        lineno = 1;
        while (fgets(line, MAXLINE, stdin) != NULL) {
            if (strstr(line, pattern) != NULL) {
                printf("%d: %s%s", lineno, line,
                       strchr(line, '\n') ? "" : "\n");
                found = 1;
            }
            lineno++;
        }
    } else {
        for (i = 2; i < argc; i++) {
            fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Error: cannot open %s\n", argv[i]);
                continue;
            }
            lineno = 1;
            while (fgets(line, MAXLINE, fp) != NULL) {
                if (strstr(line, pattern) != NULL) {
                    printf("%s:%d: %s%s", argv[i], lineno, line,
                           strchr(line, '\n') ? "" : "\n");
                    found = 1;
                }
                lineno++;
            }
            fclose(fp);
        }
    }

    return found ? 0 : 1;
}
