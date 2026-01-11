/*Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for 
each word, a list of the line numbers on which it occurs. Remove noise words like ``the,'' 
``and,'' and so on.  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define NOISEWORDS 8

struct tnode {
    char *word;
    int *lines;
    int count;
    int capacity;
    struct tnode *left;
    struct tnode *right;
};

const char *noise[NOISEWORDS] = {
    "the", "and", "a", "an", "of", "to", "in", "on"
};

int getword(char *word, int lim, int *line);
int isnoise(const char *w);
struct tnode *addtree(struct tnode *p, char *w, int line);
void treeprint(struct tnode *p);

int getword(char *word, int lim, int *line) {
    int c, d;
    char *w = word;

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            (*line)++;
        if (!isspace(c))
            break;
    }

    if (c == EOF)
        return EOF;

    if (c == '#') {
        while ((c = getchar()) != EOF && c != '\n')
            ;
        (*line)++;
        return getword(word, lim, line);
    }

    if (c == '"') {
        while ((c = getchar()) != EOF) {
            if (c == '\n')
                (*line)++;
            if (c == '\\')
                getchar();
            else if (c == '"')
                break;
        }
        return getword(word, lim, line);
    }

    if (c == '\'') {
        while ((c = getchar()) != EOF) {
            if (c == '\n')
                (*line)++;
            if (c == '\\')
                getchar();
            else if (c == '\'')
                break;
        }
        return getword(word, lim, line);
    }

    if (c == '/') {
        d = getchar();
        if (d == '/') {
            while ((c = getchar()) != EOF && c != '\n')
                ;
            (*line)++;
            return getword(word, lim, line);
        }
        if (d == '*') {
            int prev = 0;
            while ((c = getchar()) != EOF) {
                if (c == '\n')
                    (*line)++;
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim, line);
        }
        ungetc(d, stdin);
    }

    if (isalpha(c) || c == '_') {
        *w++ = tolower(c);
        while (--lim > 0) {
            c = getchar();
            if (isalnum(c) || c == '_')
                *w++ = tolower(c);
            else {
                if (c == '\n')
                    (*line)++;
                ungetc(c, stdin);
                break;
            }
        }
        *w = '\0';
        return word[0];
    }

    return c;
}

int isnoise(const char *w) {
    for (int i = 0; i < NOISEWORDS; i++)
        if (strcmp(w, noise[i]) == 0)
            return 1;
    return 0;
}

struct tnode *addtree(struct tnode *p, char *w, int line) {
    int cond;

    if (p == NULL) {
        p = malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->capacity = 10;
        p->lines = malloc(p->capacity * sizeof(int));
        p->lines[0] = line;
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        if (p->lines[p->count - 1] != line) {
            if (p->count >= p->capacity) {
                p->capacity *= 2;
                p->lines = realloc(p->lines, p->capacity * sizeof(int));
            }
            p->lines[p->count++] = line;
        }
    } else if (cond < 0)
        p->left = addtree(p->left, w, line);
    else
        p->right = addtree(p->right, w, line);

    return p;
}

void treeprint(struct tnode *p) {
    if (p) {
        treeprint(p->left);
        printf("%s:", p->word);
        for (int i = 0; i < p->count; i++)
            printf(" %d", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

int main(void) {
    struct tnode *root = NULL;
    char word[MAXWORD];
    int line = 1;

    while (getword(word, MAXWORD, &line) != EOF)
        if (isalpha(word[0]) && !isnoise(word))
            root = addtree(root, word, line);

    treeprint(root);
    return 0;
}
/*output

This is a test.
This test is simple.
is: 1 2
simple: 2
test: 1 2
this: 1 2

The cat and the dog are in the house.
The dog is on the mat.
are: 1
cat: 1
dog: 1 2
house: 1
is: 2
mat: 2

Hello hello HELLO
Hello again
again: 4
hello: 1 2 3

int main() {
    int a = 10; // this is a comment
    int b = a;  /* multi
                  line comment */                          /*
}
b: 3
int: 1 2 3
main: 1

printf("this is a test");
char c = 'a';
test again
again: 4
c: 2
char: 2
printf: 1
test: 3
*/