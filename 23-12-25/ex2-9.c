/* In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit 
in x. Explain why. Use this observation to write a faster version of bitcount. */
#include <stdio.h>

int bitcount(unsigned int x) {
    int count = 0;

    while (x != 0) {
        x &= (x - 1);  
        count++;
    }

    return count;
}

int main() {
    unsigned int x;

    printf("Enter a number: ");
    scanf("%u", &x);

    printf("Number of 1-bits = %d\n", bitcount(x));
    return 0;
}

/* output
Enter a number: 0
Number of 1-bits = 0

Enter a number: 8
Number of 1-bits = 1

Enter a number: 15
Number of 1-bits = 4

Enter a number: 4294967295
Number of 1-bits = 32

Enter a number: 13
Number of 1-bits = 3
*/
