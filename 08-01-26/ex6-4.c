/*Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing 
order of frequency of occurrence. Precede each word by its count.  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct word {
    char *w;
    int count;
};

struct word *words = NULL;
int nwords = 0;
int capacity = 0;

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while ((c = getchar()) != EOF && !isalpha(c))
        ;

    if (c == EOF)
        return EOF;

    *w++ = tolower(c);

    while (--lim > 0 && (c = getchar()) != EOF && isalpha(c))
        *w++ = tolower(c);

    if (isalpha(c))
        while ((c = getchar()) != EOF && isalpha(c))
            ;

    *w = '\0';
    return word[0];
}

void addword(char *word) {
    for (int i = 0; i < nwords; i++) {
        if (strcmp(words[i].w, word) == 0) {
            words[i].count++;
            return;
        }
    }

    if (nwords >= capacity) {
        capacity = capacity ? capacity * 2 : 64;
        struct word *tmp = realloc(words, capacity * sizeof(struct word));
        if (tmp == NULL) {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        words = tmp;
    }

    words[nwords].w = strdup(word);
    if (words[nwords].w == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    words[nwords].count = 1;
    nwords++;
}

int cmp(const void *a, const void *b) {
    const struct word *wa = a;
    const struct word *wb = b;

    if (wb->count != wa->count)
        return wb->count - wa->count;

    return strcmp(wa->w, wb->w);
}

int main(void) {
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        addword(word);

    if (nwords > 1)
        qsort(words, nwords, sizeof(struct word), cmp);

    for (int i = 0; i < nwords; i++)
        printf("%4d %s\n", words[i].count, words[i].w);

    for (int i = 0; i < nwords; i++)
        free(words[i].w);

    free(words);
    return 0;
}
/*output

This is a test this is only a test
   2 a
   2 is
   2 test
   2 this
   1 only

Hello, hello! HELLO world world.
   3 hello
   2 world

C programming in C is fun, fun, fun!!!
   3 fun
   2 c
   1 in
   1 is
   1 programming

Apple Apple Apple
   3 apple

123 !! @@ ##

*/