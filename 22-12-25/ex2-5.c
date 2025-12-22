/*Write the function any(s1,s2), which returns the first location in a string s1 
where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. 
(The standard library function strpbrk does the same job but returns a pointer to the 
location.)  */
#include <stdio.h>
#include <ctype.h>

int any(char s1[], char s2[]) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (tolower(s1[i]) == tolower(s2[j]))
                return i;
        }
    }
    return -1;
}

int main() {
    char s1[100], s2[100];
    printf("Enter first string: ");
    scanf("%99s", s1);
    printf("Enter second string: ");
    scanf("%99s", s2);
    int pos = any(s1, s2);
    printf("Result: %d\n", pos);
    return 0;
}

/*output
Enter first string: hi
Enter second string: you
Result: -1

Enter first string: hello_world
Enter second string: land
Result: 2
*/
