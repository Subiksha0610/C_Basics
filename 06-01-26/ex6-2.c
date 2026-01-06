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

int getword(char *word, int lim);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p, int prefixlen, char *last);
int sameprefix(const char *a, const char *b, int n);

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

    if (last[0] == '\0' || strcmp(cur, last) != 0) {
        strcpy(last, cur);
        int found = 0;

        struct tnode *q = p;
        while (q) {
            if (sameprefix(q->word, p->word, prefixlen))
                found = 1;
            q = q->right;
        }

        if (found)
            printf("\nGroup: %s\n", cur);
        else
            goto skip;
    }

    printf("    %s\n", p->word);

skip:
    treeprint(p->right, prefixlen, last);
}

int main(int argc, char *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];
    char last[MAXWORD] = "";
    int prefixlen = 6;

    if (argc > 1)
        prefixlen = atoi(argv[1]);

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);

    treeprint(root, prefixlen, last);
    return 0;
}
