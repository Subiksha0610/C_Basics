#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[]) {
    FILE *fp1 = NULL, *fp2 = NULL;
    char line1[MAXLINE], line2[MAXLINE];
    int lineno = 1;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");
    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr, "Error: cannot open one of the files.\n");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        return 1;
    }

    while (1) {
        char *r1 = fgets(line1, MAXLINE, fp1);
        char *r2 = fgets(line2, MAXLINE, fp2);

        if (r1 == NULL && r2 == NULL) {
            printf("Files are identical.\n");
            break;
        }

        if (r1 == NULL || r2 == NULL ||
            strcmp(line1, line2) != 0 ||
            (r1 && r2 &&
             strchr(line1, '\n') == NULL &&
             strchr(line2, '\n') != NULL) ||
            (r1 && r2 &&
             strchr(line1, '\n') != NULL &&
             strchr(line2, '\n') == NULL)) {

            printf("Files differ at line %d:\n", lineno);

            if (r1) printf("File1: %s%s", line1,
                            strchr(line1, '\n') ? "" : "\n");
            else printf("File1: [EOF]\n");

            if (r2) printf("File2: %s%s", line2,
                            strchr(line2, '\n') ? "" : "\n");
            else printf("File2: [EOF]\n");
            break;
        }
        lineno++;
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
