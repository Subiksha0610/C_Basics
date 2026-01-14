/*Exercise 7-8. Write a program to print a set of files, starting each new one on a new page, 
with a title and a running page count for each file.  */
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
/*output
subiksha@DESKTOP-CBQDRR5:~$ ./ex7-8 file1.txt
=== file1.txt (Page 1) ===
Hello
World
------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex7-8 file2.txt
=== file2.txt (Page 1) ===
all good
-------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ nano empty.txt
subiksha@DESKTOP-CBQDRR5:~$ ./ex7-8 empty.txt
=== empty.txt (Page 1) ===
-------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex7-8 file2.txt file1.txt
=== file2.txt (Page 1) ===
Line 1
 Line 2
 Line 3
 Line 4
 Line 5
 Line 6
 Line 7
 Line 8
 9
Line 10
 Line 11
 Line 12
 Line 13
 Line 14
 15
Line 16
 Line 17
 Line 18
 Line 19
 Line 20
Line 21
 Line 22
 Line 23
 Line 24
 Line 25
 Line 26
 Line 27
 Line 28
 Line 29
Line 30
Line 31
Line 32
Line 33
Line 34
Line 35
Line 36
Line 37
Line 38
Line 39
Line 40
Line 41
42
Line 43
Line 44
Line 45
Line 46
Line 47
Line 48
Line 49
Line 50

=== file2.txt (Page 2) ===
Line 51
Line 52

=== file1.txt (Page 1) ===
Hello
World
--------------------------------------------------------
subiksha@DESKTOP-CBQDRR5:~$ ./ex7-8 file3.txt
=== file3.txt (Page 1) ===
linewithoutline

*/