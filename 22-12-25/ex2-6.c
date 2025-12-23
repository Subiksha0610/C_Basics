/*Write a function setbits(x,p,n,y) that returns x with the n bits that begin at 
position p set to the rightmost n bits of y, leaving the other bits unchanged. */
#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    return (x & ((~0 << n) << (p+1-n))) | ((y & ~(~0 << n)) << (p+1-n));
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

/*output
Enter x: 200
Enter p: 4
Enter n: 3
Enter y: 7
Result: 220
*/
