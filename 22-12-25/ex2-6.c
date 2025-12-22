#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (x & ~(~(~0 << n) << (p+1-n))) | ((y & ~(~0 << n)) << (p+1-n));
}

int main() {
    unsigned x, y;
    int p, n;
    printf("Enter x: ");
    scanf("%u", &x);
    printf("Enter p: ");
    scanf("%d", &p);
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter y: ");
    scanf("%u", &y);
    unsigned result = setbits(x, p, n, y);
    printf("Result: %u\n", result);
    return 0;
}
