/* Write a function rightrot(x,n) that returns the value of the integer x rotated 
to the right by n positions. */
#include <stdio.h>

unsigned rightrot(unsigned x, int n) {
    int wordlen = sizeof(x) * 8;
    return (x >> n) | (x << (wordlen - n));
}

int main() {
    unsigned x;
    int n;
    printf("Enter x: ");
    scanf("%u", &x);
    printf("Enter n: ");
    scanf("%d", &n);
    unsigned result = rightrot(x, n);
    printf("Result: %u\n", result);
    return 0;
}

/* output
Enter x: 300
Enter n: 3
Result: 2147483685
*/
