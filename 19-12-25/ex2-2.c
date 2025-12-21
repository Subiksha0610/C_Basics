//Write a loop equivalent to the for loop above without using && or ||. 
#include <stdio.h>
int main() {
    int fahr;

    fahr = 0;
    while (fahr <= 300) {
        printf("%3d %6.1f\n", fahr, (5.0/9.0) * (fahr - 32));
        fahr = fahr + 20;
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
