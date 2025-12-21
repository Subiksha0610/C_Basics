/*Write a program to determine the ranges of char, short, int, and long 
variables, both signed and unsigned, by printing appropriate values from standard headers 
and by direct computation. Harder if you compute them: determine the ranges of the various 
floating-point types. */

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("CHAR range: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("UNSIGNED CHAR range: 0 to %u\n", UCHAR_MAX);

    printf("INT range: %d to %d\n", INT_MIN, INT_MAX);
    printf("UNSIGNED INT range: 0 to %u\n", UINT_MAX);

    printf("LONG range: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("UNSIGNED LONG range: 0 to %lu\n", ULONG_MAX);

    printf("FLOAT range: %e to %e\n", FLT_MIN, FLT_MAX);
    printf("DOUBLE range: %e to %e\n", DBL_MIN, DBL_MAX);

    return 0;
}

/* output
CHAR range: -128 to 127
UNSIGNED CHAR range: 0 to 255
INT range: -2147483648 to 2147483647
UNSIGNED INT range: 0 to 4294967295
LONG range: -9223372036854775808 to 9223372036854775807
UNSIGNED LONG range: 0 to 18446744073709551615
FLOAT range: 1.175494e-38 to 3.402823e+38
DOUBLE range: 2.225074e-308 to 1.797693e+308
*/
