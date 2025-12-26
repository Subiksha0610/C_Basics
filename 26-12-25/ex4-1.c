/*Write the function strindex(s,t) which returns the position of the rightmost 
occurrence of t in s, or -1 if there is none.  */
#include <stdio.h>
#include <string.h>

int strindex(char s[], char t[]) {
    int i, j, k;
    int pos = -1;

    if (t[0] == '\0')
        return 0;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (t[k] == '\0')
            pos = i;
    }
    return pos;
}

int main() {
    char s[100], t[100];
    int index;

    printf("Enter main string: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';

    printf("Enter substring: ");
    fgets(t, sizeof(t), stdin);
    t[strcspn(t, "\n")] = '\0';

    index = strindex(s, t);

    if (index != -1)
        printf("Rightmost occurrence index: %d\n", index);
    else
        printf("Substring not found\n");

    return 0;
}
