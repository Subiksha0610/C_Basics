/*Write a function invert(x,p,n) that returns x with the n bits that begin at 
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.  */
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
/*output
Enter x: 200
Enter p: 4
Enter n: 3
Result: 212
*/
