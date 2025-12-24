#include <stdio.h>

int binsearch(int x, int v[], int n) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        if (v[mid] == x)
            return mid;
    }
    return -1;
}

int main() {
    int v[] = {1, 3, 5, 7, 9, 11, 13};
    int n = sizeof(v) / sizeof(v[0]);
    int x = 7;
    int result = binsearch(x, v, n);
    if (result != -1)
        printf("Found %d at index %d\n", x, result);
    else
        printf("%d not found\n", x);
    return 0;
}
