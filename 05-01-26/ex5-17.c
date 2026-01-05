/*Exercise 5-17. Add a field-searching capability, so sorting may bee done on fields within 
lines, each field sorted according to an independent set of options. (The index for this book 
was sorted with -df for the index category and -n for the page numbers.) */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN   1000
#define MAXFIELDS 10

char *lineptr[MAXLINES];

struct fieldopt {
    int fieldno;
    int numeric;
    int fold;
    int directory;
} fieldopts[MAXFIELDS];

int nfields = 0;

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
int my_getline(char *s, int lim);

void qsort_custom(void *lineptr[], int left, int right,
                  int (*comp)(const char *, const char *));
int fieldcmp(const char *s, const char *t);

char *extract_field(const char *line, int fieldno);
int charcmp(const char *s, const char *t, int fold, int directory, int numeric);

int main(int argc, char *argv[]) {
    int nlines;

    while (--argc > 0) {
        char *arg = *++argv;
        if (arg[0] == '-') {
            struct fieldopt fo = {0,0,0,0};
            char *p = arg+1;
            while (*p && *p != ':') {
                if (*p == 'd') fo.directory = 1;
                else if (*p == 'f') fo.fold = 1;
                else if (*p == 'n') fo.numeric = 1;
                p++;
            }
            if (*p == ':')
                fo.fieldno = atoi(p+1);
            if (nfields < MAXFIELDS)
                fieldopts[nfields++] = fo;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_custom((void **)lineptr, 0, nlines-1,
            (int (*)(const char *, const char *))fieldcmp);
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
    void *t = v[i];
    v[i] = v[j];
    v[j] = t;
}

int fieldcmp(const char *s, const char *t) {
    int i, r;
    for (i = 0; i < nfields; i++) {
        char *fs = extract_field(s, fieldopts[i].fieldno);
        char *ft = extract_field(t, fieldopts[i].fieldno);
        r = charcmp(fs, ft,
                    fieldopts[i].fold,
                    fieldopts[i].directory,
                    fieldopts[i].numeric);
        free(fs);
        free(ft);
        if (r != 0)
            return r;
    }
    return strcmp(s, t);
}

char *extract_field(const char *line, int fieldno) {
    const char *p = line;
    int f = 0;

    while (*p && f < fieldno) {
        while (*p && !isspace((unsigned char)*p)) p++;
        while (*p && isspace((unsigned char)*p)) p++;
        f++;
    }

    if (!*p) {
        char *e = malloc(1);
        e[0] = '\0';
        return e;
    }

    const char *start = p;
    while (*p && !isspace((unsigned char)*p)) p++;

    int len = p - start;
    char *field = malloc(len + 1);
    strncpy(field, start, len);
    field[len] = '\0';
    return field;
}

int charcmp(const char *s, const char *t, int fold, int directory, int numeric) {
    if (numeric) {
        if (*s == '\0' && *t == '\0') return 0;
        if (*s == '\0') return -1;
        if (*t == '\0') return 1;
        double v1 = atof(s);
        double v2 = atof(t);
        if (v1 < v2) return -1;
        if (v1 > v2) return 1;
        return 0;
    }

    for (;;) {
        if (directory) {
            while (*s && !isalnum((unsigned char)*s) && !isspace((unsigned char)*s)) s++;
            while (*t && !isalnum((unsigned char)*t) && !isspace((unsigned char)*t)) t++;
        }

        if (*s == '\0' || *t == '\0')
            return *s - *t;

        char a = fold ? tolower((unsigned char)*s) : *s;
        char b = fold ? tolower((unsigned char)*t) : *t;

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
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-17 -df:0 -n:1
apple 10
banana
cherry 2


apple 10
banana
cherry 2
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-17 -df:0
Zoo!
apple#
Ball@


apple#
Ball@
Zoo!
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-17 -n:1
item 5
item
item 2


item
item 2
item 5
subiksha@DESKTOP-CBQDRR5:~$ ./ex5-17 -df:0
cat a
cat b
cat c


cat a
cat b
cat c
*/