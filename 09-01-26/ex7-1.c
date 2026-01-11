/*Exercise 7-1. Write a program that converts upper case to lower or lower case to upper, 
depending on the name it is invoked with, as found in argv[0]. */
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
/*output
subiksha@DESKTOP-CBQDRR5:~$ gcc ex7-1.c -o lower
subiksha@DESKTOP-CBQDRR5:~$ ./lower
Hello
hello
HELLO WORLD
hello world
subiksha@DESKTOP-CBQDRR5:~$ gcc ex7-1.c -o upper
subiksha@DESKTOP-CBQDRR5:~$ ./upper
hello world
HELLO WORLD
*/