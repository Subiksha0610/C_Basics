/*Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each 
group of variable names that are identical in the first 6 characters, but different somewhere 
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be 
set from the command line. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", 
    "double", "else", "enum", "extern", "float", "for", "goto", "if", 
    "inline", "int", "long", "register", "restrict", "return", "short", 
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", 
    "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};
#define NKEYWORDS (sizeof(keywords)/sizeof(keywords[0]))

int getword(char *word, int lim);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p, int prefixlen, char *last);
int sameprefix(const char *a, const char *b, int n);
int iskeyword(const char *w);

int main(int argc, char *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];
    char last[MAXWORD] = "";
    int prefixlen = 6;

    if (argc > 1)
        prefixlen = atoi(argv[1]);

    while (getword(word, MAXWORD) != EOF)
        if ((isalpha(word[0]) || word[0] == '_') && !iskeyword(word))
            root = addtree(root, word);

    treeprint(root, prefixlen, last);
    return 0;
}

int getword(char *word, int lim) {
    int c, d;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c == EOF)
        return EOF;

    if (c == '#') {
        while ((c = getchar()) != EOF && c != '\n')
            if (c == '\\')
                getchar();
        return getword(word, lim);
    }

    if (c == '"') {
        while ((c = getchar()) != EOF) {
            if (c == '\\')
                getchar();
            else if (c == '"')
                break;
        }
        return getword(word, lim);
    }

    if (c == '\'') {
        while ((c = getchar()) != EOF) {
            if (c == '\\')
                getchar();
            else if (c == '\'')
                break;
        }
        return getword(word, lim);
    }

    if (c == '/') {
        d = getchar();
        if (d == '/') {
            while ((c = getchar()) != EOF && c != '\n')
                ;
            return getword(word, lim);
        }
        if (d == '*') {
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        }
        ungetc(d, stdin);
    }

    if (!isalpha(c) && c != '_')
        return c;

    *w++ = c;
    while (--lim > 0) {
        c = getchar();
        if (!isalnum(c) && c != '_') {
            ungetc(c, stdin);
            break;
        }
        *w++ = c;
    }
    *w = '\0';
    return word[0];
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

int sameprefix(const char *a, const char *b, int n) {
    return strncmp(a, b, n) == 0 && strcmp(a, b) != 0;
}

void treeprint(struct tnode *p, int prefixlen, char *last) {
    char cur[MAXWORD];

    if (p == NULL)
        return;

    treeprint(p->left, prefixlen, last);

    strncpy(cur, p->word, prefixlen);
    cur[prefixlen] = '\0';

    if (last[0] == '\0' || strncmp(last, cur, prefixlen) != 0) {
        if (last[0] != '\0')
            printf("\n");
        strcpy(last, cur);
        printf("Group: %s\n", cur);
    }

    printf("    %s\n", p->word);

    treeprint(p->right, prefixlen, last);
}

int iskeyword(const char *w) {
    for (int i = 0; i < NKEYWORDS; i++)
        if (strcmp(w, keywords[i]) == 0)
            return 1;
    return 0;
}

/*
output

int dataOne;
int dataTwo;
int dateValue;

Group: data
    dataOne
    dataTwo

int sampleValue;
/* int sampleFake; */                          /*
char *s = "sampleText";
int sampleCount;
int sampleIndex;

Group: sample
    sampleCount
    sampleIndex
    sampleValue

int apple;
int banana;
int carrot;
//no output

int counterValue;
int counterTotal;
int counterIndex;
int count;

float counterRate;
float counterMax;

Group: count
    count

Group: counte
    counterIndex
    counterMax
    counterRate
    counterTotal
    counterValue
*/