#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void *mycalloc(size_t n, size_t size) {
    if (n == 0 || size == 0)
        return NULL;

    if (size != 0 && n > SIZE_MAX / size)
        return NULL;

    size_t total = n * size;
    void *p = malloc(total);
    if (p != NULL) {
        memset(p, 0, total);
    }
    return p;
}

int main(void) {
    int *arr;
    int i, n = 5;

    arr = (int *) mycalloc(n, sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    free(arr);
    return 0;
}
