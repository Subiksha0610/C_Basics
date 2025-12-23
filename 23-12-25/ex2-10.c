/*Rewrite the function lower, which converts upper case letters to lower case, 
with a conditional expression instead of if-else.  */
#include <stdio.h>

int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
}

int main() {
    char c;

    printf("Enter a character: ");
    scanf(" %c", &c);  

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        printf("Output: %c\n", lower(c));
    } else {
        printf("Error: Enter a proper alphabet\n");
    }

    return 0;
}

/*output
Enter a character: A
Output: a

Enter a character: Z
Output: z

Enter a character: m
Output: m

Enter a character: 7
Error: Enter a proper alphabet

Enter a character: @
Error: Enter a proper alphabet

Enter a character:
Error: Enter a proper alphabet

Enter a character: [
Error: Enter a proper alphabet

Enter a character: \t
Error: Enter a proper alphabet
*/
