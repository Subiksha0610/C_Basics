/*Our binary search makes two tests inside the loop, when one would suffice (at 
the price of more tests outside.) Write a version with only one test inside the loop and 
measure the difference in run-time. */
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
/*output
Found 7 at index 3
*/