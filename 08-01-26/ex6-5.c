/*Exercise 6-5. Write a function undef that will remove a name and definition from the table 
maintained by lookup and install. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
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
        if (np->name == NULL) {
            free(np);
            return NULL;
        }

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

void undef(char *name) {
    struct nlist *np, *prev;
    unsigned hashval;

    if (name == NULL)
        return;

    hashval = hash(name);
    prev = NULL;

    for (np = hashtab[hashval]; np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0) {
            if (prev == NULL)
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;

            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
        prev = np;
    }
}

void print_table(void) {
    for (int i = 0; i < HASHSIZE; i++) {
        for (struct nlist *np = hashtab[i]; np != NULL; np = np->next)
            printf("%s -> %s\n", np->name, np->defn);
    }
}

int main(void) {
    install("PI", "3.14159");
    install("E", "2.71828");
    install("GOLDEN", "1.61803");

    printf("Table after installs:\n");
    print_table();

    undef("E");
    undef(NULL);
    install(NULL, "123");
    install("X", NULL);

    printf("\nTable after edge case operations:\n");
    print_table();

    return 0;
}
/*output
Table after installs:
PI -> 3.14159
E -> 2.71828
GOLDEN -> 1.61803

Table after edge case operations:
PI -> 3.14159
GOLDEN -> 1.61803
*/