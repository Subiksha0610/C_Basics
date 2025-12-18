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

/*output
  0  -17.8
 20   -6.7
 40    4.4
 60   15.6
 80   26.7
100   37.8
120   48.9
140   60.0
160   71.1
180   82.2
200   93.3
220  104.4
240  115.6
260  126.7
280  137.8
300  148.9
*/
