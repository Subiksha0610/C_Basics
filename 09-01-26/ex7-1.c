#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int c;
    int tolower_mode = 0;
    int toupper_mode = 0;

    if (argv[0] != NULL) {
        char name[100];
        int i = 0;
        while (argv[0][i] && i < 99) {
            name[i] = tolower((unsigned char)argv[0][i]);
            i++;
        }
        name[i] = '\0';

        if (strstr(name, "lower") != NULL)
            tolower_mode = 1;
        if (strstr(name, "upper") != NULL)
            toupper_mode = 1;
    }

    if (tolower_mode && !toupper_mode) {
        while ((c = getchar()) != EOF)
            putchar(tolower((unsigned char)c));
    } else {
        while ((c = getchar()) != EOF)
            putchar(toupper((unsigned char)c));
    }

    return 0;
}
