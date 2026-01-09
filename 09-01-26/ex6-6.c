#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval = 0;
    while (*s)
        hashval = *s++ + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    if (s == NULL)
        return NULL;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if (name == NULL || defn == NULL)
        return NULL;

    if ((np = lookup(name)) == NULL) {
        np = malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->name = strdup(name);
        if (np->name == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free(np->defn);
    }

    np->defn = strdup(defn);
    if (np->defn == NULL)
        return NULL;

    return np;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while ((c = getchar()) != EOF && isspace(c))
        ;

    if (c == EOF)
        return EOF;

    *w++ = c;

    if (!isalpha(c) && c != '#') {
        *w = '\0';
        return c;
    }

    while (--lim > 0 && (c = getchar()) != EOF && !isspace(c))
        *w++ = c;

    *w = '\0';
    return word[0];
}

int main(void) {
    char word[MAXWORD];
    char name[MAXWORD];
    char defn[MAXWORD];
    struct nlist *np;

    while (getword(word, MAXWORD) != EOF) {
        if (strcmp(word, "#define") == 0) {
            if (getword(name, MAXWORD) == EOF)
                continue;
            if (getword(defn, MAXWORD) == EOF)
                defn[0] = '\0';
            install(name, defn);
        } else if (isalpha(word[0])) {
            np = lookup(word);
            if (np != NULL)
                printf("%s", np->defn);
            else
                printf("%s", word);
        } else {
            printf("%s", word);
        }
    }
    return 0;
}
