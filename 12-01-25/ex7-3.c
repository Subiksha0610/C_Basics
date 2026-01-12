/*Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.  
*/
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

void minprintf(const char *fmt, ...);

int main(void) {
    minprintf("Percent: %%\n");
    minprintf("Width *: %*d\n", 6, 42);
    minprintf("Precision *: %.*f\n", 3, 3.14159);
    minprintf("NULL string: %s\n", NULL);
    minprintf("Long int: %ld\n", 1234567890L);
    return 0;
}

void minprintf(const char *fmt, ...) {
    va_list ap;
    const char *p;
    char *sval;
    int ival;
    unsigned uval;
    long lval;
    unsigned long ulval;
    double dval;
    char format[100];

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        if (*(p + 1) == '%') {
            putchar('%');
            p++;
            continue;
        }

        char *f = format;
        *f++ = '%';

        p++;
        while (*p && strchr("-+ #0", *p)) *f++ = *p++;

        if (*p == '*') {
            *f++ = *p++;
        } else {
            while (*p && isdigit(*p)) *f++ = *p++;
        }

        if (*p == '.') {
            *f++ = *p++;
            if (*p == '*') {
                *f++ = *p++;
            } else {
                while (*p && isdigit(*p)) *f++ = *p++;
            }
        }

        if (*p && strchr("hlL", *p)) *f++ = *p++;

        if (*p) {
            *f++ = *p;
            *f = '\0';
        } else {
            break;
        }

        switch (*p) {
        case 'd': case 'i':
            if (strchr(format, 'l'))
                printf(format, va_arg(ap, long));
            else
                printf(format, va_arg(ap, int));
            break;
        case 'u': case 'o': case 'x': case 'X':
            if (strchr(format, 'l'))
                printf(format, va_arg(ap, unsigned long));
            else
                printf(format, va_arg(ap, unsigned));
            break;
        case 'c':
            printf(format, va_arg(ap, int));
            break;
        case 's':
            sval = va_arg(ap, char *);
            if (sval == NULL) sval = "(null)";
            printf(format, sval);
            break;
        case 'f': case 'e': case 'E': case 'g': case 'G':
            printf(format, va_arg(ap, double));
            break;
        case 'p':
            printf(format, va_arg(ap, void *));
            break;
        default:
            putchar('%');
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}
/*output
Percent: %
Width *:      6
Precision *: 3.141589999999999882618340052431449294090270996093750000000000000000000000000000000000000000000000000000
NULL string: (null)
Long int: 1234567890
*/