#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define LINES_PER_PAGE 50

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAXLINE];

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int page = 1;
        int linecount = 0;

        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: cannot open %s\n", argv[i]);
            continue;
        }

        printf("=== %s (Page %d) ===\n", argv[i], page);

        while (fgets(line, MAXLINE, fp) != NULL) {
            if (linecount == LINES_PER_PAGE) {
                printf("\f");
                page++;
                linecount = 0;
                printf("=== %s (Page %d) ===\n", argv[i], page);
            }
            fputs(line, stdout);
            if (line[strlen(line) - 1] != '\n')
                putchar('\n');
            linecount++;
        }

        fclose(fp);

        if (i < argc - 1)
            printf("\f");
    }

    return 0;
}
