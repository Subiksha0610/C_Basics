#include <stdio.h>

unsigned invert(unsigned x, int p, int n) {
    return x ^ (~(~0 << n) << (p+1-n));
}

int main() {
    unsigned x;
    int p, n;
    printf("Enter x: ");
    scanf("%u", &x);
    printf("Enter p: ");
    scanf("%d", &p);
    printf("Enter n: ");
    scanf("%d", &n);
    unsigned result = invert(x, p, n);
    printf("Result: %u\n", result);
    return 0;
}
