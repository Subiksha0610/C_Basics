/*Exercise 5-16. Add the -d (``directory order'') option, which makes comparisons only on 
letters, numbers and blanks. Make sure it works in conjunction with -f.  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN   1000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int my_getline(char *s, int lim);

void qsort_custom(void *lineptr[], int left, int right,
                  int (*comp)(const char *, const char *));
int charcmp(const char *s, const char *t);

int option_d = 0;
int option_f = 0;

int main(int argc, char *argv[]) {
    int nlines;
    int c;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
            case 'd': option_d = 1; break;
            case 'f': option_f = 1; break;
            default: return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_custom((void **) lineptr, 0, nlines-1,
            (int (*)(const char *, const char *)) charcmp);
        writelines(lineptr, nlines);
        return 0;
    }
    return 1;
}

void qsort_custom(void *v[], int left, int right,
                  int (*comp)(const char *, const char *)) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_custom(v, left, last-1, comp);
    qsort_custom(v, last+1, right, comp);
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int charcmp(const char *s, const char *t) {
    char a, b;

    for (;;) {
        if (option_d) {
            while (*s && !isalnum((unsigned char)*s) && !isspace((unsigned char)*s))
                s++;
            while (*t && !isalnum((unsigned char)*t) && !isspace((unsigned char)*t))
                t++;
        }

        if (*s == '\0' || *t == '\0')
            return *s - *t;

        a = option_f ? tolower((unsigned char)*s) : *s;
        b = option_f ? tolower((unsigned char)*t) : *t;

        if (a != b)
            return a - b;

        s++;
        t++;
    }
}

int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len+1)) == NULL)
            return -1;
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}

int my_getline(char *s, int lim) {
    int c, i;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}
/*output
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-16
abc!
abc#
abc$


abc!
abc#
abc$
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-16 -d
abc!
abc#
abc$


abc#
abc$
abc!
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-16 -df
Zoo!
apple#
Ball@


apple#
Ball@
Zoo!
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-16 -d
!!!
abc
###


!!!
###
abc

subiksha@DESKTOP-CBQDRR5:~$ ./ex5-16 -df
a-b
a b
A@b


a b
A@b
a-b
*/
