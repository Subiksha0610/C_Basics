/*Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous 
section.  */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

void minscanf(const char *fmt, ...);

int main(void) {
    int ival;
    float fval;
    char str[10];

    printf("Enter an int, a float, and a string:\n");
    minscanf("%d %f %9s", &ival, &fval, str);

    printf("You entered: int=%d, float=%.2f, string=%s\n", ival, fval, str);
    return 0;
}

void minscanf(const char *fmt, ...) {
    va_list ap;
    const char *p;
    int *ip;
    float *fp;
    char *sp;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {

        if (*p != '%')
            continue;

        p++;

        switch (*p) {

        case 'd':
            ip = va_arg(ap, int *);
            if (scanf("%d", ip) != 1)
                goto done;
            break;

        case 'f':
            fp = va_arg(ap, float *);
            if (scanf("%f", fp) != 1)
                goto done;
            break;

        case 's':
            sp = va_arg(ap, char *);
            if (scanf("%99s", sp) != 1)
                goto done;
            break;

        case '%':
            getchar();
            break;

        default:
            break;
        }
    }
done:
    va_end(ap);
}
/*output
Enter an int, a float, and a string:
50%
You entered: int=50, float=0.00, string=

Enter an int, a float, and a string:
A
You entered: int=0, float=-0.00, string=

Enter an int, a float, and a string:
10
You entered: int=10, float=-0.00, string=

Enter an int, a float, and a string:
10 3.14 hello
You entered: int=10, float=3.14, string=hello

Enter an int, a float, and a string:
5 2.5 verylongstring
You entered: int=5, float=2.50, string=verylongs

*/
