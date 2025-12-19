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
