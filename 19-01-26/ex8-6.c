/*Exercise 8-6. The standard library function calloc(n,size) returns a pointer to n objects of 
size size, with the storage initialized to zero. Write calloc, by calling malloc or by 
modifying it. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

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
/*output
arr[0] = 0
arr[1] = 0
arr[2] = 0
arr[3] = 0
arr[4] = 0
*/