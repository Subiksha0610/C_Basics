/*Write the function strend(s,t), which returns 1 if the string t occurs at the 
end of the string s, and zero otherwise.  */
#include <stdio.h>

int strend(char *s, char *t) {
    char *bs, *bt;

    if (s == NULL || t == NULL)
        return 0;

    bs = s;
    bt = t;

    while (*s) s++;
    while (*t) t++;

    if (t - bt > s - bs)
        return 0;

    while (t > bt) {
        if (*--s != *--t)
            return 0;
    }
    return 1;
}

int main(void) {
    char s1[] = "hello world";
    char t1[] = "world";
    char t2[] = "hello";
    char t3[] = "";

    printf("%d\n", strend(s1, t1));
    printf("%d\n", strend(s1, t2));
    printf("%d\n", strend(s1, t3));

    char s2[] = "C programming";
    char t4[] = "ming";
    char t5[] = "program";

    printf("%d\n", strend(s2, t4));
    printf("%d\n", strend(s2, t5));

    char s3[] = "";
    char t6[] = "abc";

    printf("%d\n", strend(s3, t6));
    printf("%d\n", strend(s3, t3));

    return 0;
}
/*output
1
0
1
1
0
0
1
*/