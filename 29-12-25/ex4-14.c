#include <stdio.h>

#define swap(t,x,y) do { t temp = (x); (x) = (y); (y) = temp; } while(0)

int main() {
    int a = 5, b = 10;
    double x = 1.2, y = 3.4;
    char c1 = 'A', c2 = 'Z';
    char *s1 = "hello", *s2 = "world";
    swap(int,a,b);
    swap(double,x,y);
    swap(char,c1,c2);
    swap(char*,s1,s2);
    swap(int,a,a);
    printf("int: a=%d b=%d\n", a, b);
    printf("double: x=%.1f y=%.1f\n", x, y);
    printf("char: c1=%c c2=%c\n", c1, c2);
    printf("string: s1=%s s2=%s\n", s1, s2);
    printf("self-swap: a=%d\n", a);
    return 0;
}
