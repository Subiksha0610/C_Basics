/*Exercise 7-7. Modify the pattern finding program of Chapter 5
 to take its input from a set of 
named files or, if no files are named as arguments, from the standard input. Should the file 
name be printed when a matching line is found? */
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
/*output
subiksha@DESKTOP-CBQDRR5:~$ gcc ex7-7.c -o find
subiksha@DESKTOP-CBQDRR5:~$ ./find error

no issue
error occurred
2: error occurred

done
hello
error here
5: error here

hello error here
6: hello error here
--------------------------------------------------
file1.txt 
hello
error here

file2.txt
all good

subiksha@DESKTOP-CBQDRR5:~$ ./find error file1.txt file2.txt
file1.txt:2: error here
------------------------------------------------------
file1.txt 
hello
error here

file2.txt
all good

subiksha@DESKTOP-CBQDRR5:~$ ./find "" file1.txt
Error: empty pattern
------------------------------------------------------
file1.txt
error

file2.txt
all good

subiksha@DESKTOP-CBQDRR5:~$ ./find error file1.txt file2.txt
file1.txt:1: error
-----------------------------------------------------------
file1.txt
error

file2.txt
all good

subiksha@DESKTOP-CBQDRR5:~$ ./find xyz file1.txt
//no output exit status=1
*/