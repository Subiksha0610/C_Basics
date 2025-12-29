/*Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t. 
(Block structure will help.)  
*/
#include <stdio.h>

#define swap(t,x,y) do { \
    if ((x) != (y)) { \
        t temp = *(x); \
        *(x) = *(y); \
        *(y) = temp; \
    } \
} while(0)

int main() {
    int a, b;
    double x, y;
    char c1, c2;
    char s1[50], s2[50];
    char *p1, *p2;

    scanf("%d %d", &a, &b);
    scanf("%lf %lf", &x, &y);
    scanf(" %c %c", &c1, &c2);
    scanf("%s %s", s1, s2);

    p1 = s1;
    p2 = s2;

    swap(int, &a, &b);
    swap(double, &x, &y);
    swap(char, &c1, &c2);
    swap(char*, &p1, &p2);
    swap(int, &a, &a);

    printf("int: a=%d b=%d\n", a, b);
    printf("double: x=%.1f y=%.1f\n", x, y);
    printf("char: c1=%c c2=%c\n", c1, c2);
    printf("string: s1=%s s2=%s\n", p1, p2);
    printf("self-swap: a=%d\n", a);

    return 0;
}

/*output
5 10
1.2 3.4
A Z
hello world
int: a=10 b=5
double: x=3.4 y=1.2
char: c1=Z c2=A
string: s1=world s2=hello
self-swap: a=10
*/
