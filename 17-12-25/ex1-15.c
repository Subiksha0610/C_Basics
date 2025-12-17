#include <stdio.h>

float fahtocel(float fah) {
    return (5.0/9.0) * (fah - 32.0);
}

int main() {
    float fah;
    int lower = 0, upper = 300, step = 20;

    for (fah = lower; fah <= upper; fah += step) {
        printf("%3.0f %6.1f\n", fah, fahtocel(fah));
    }

    return 0;
}
