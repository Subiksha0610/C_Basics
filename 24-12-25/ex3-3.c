/*Write a function expand(s1,s2) that expands shorthand notations like a-z in 
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either 
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange 
that a leading or trailing - is taken literally.*/
#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]) {
    int i, j;
    for (i = j = 0; s1[i] != '\0'; i++) {

        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0') {
            char prev = s1[i-1];
            char next = s1[i+1];

            // Only expand if both are digits OR both uppercase OR both lowercase
            int valid_range = 0;
            if ((isdigit(prev) && isdigit(next)) ||
                (isupper(prev) && isupper(next)) ||
                (islower(prev) && islower(next)))
                valid_range = 1;

            if (valid_range && prev < next) {
                char start = prev + 1;
                while (start < next)
                    s2[j++] = start++;
                continue;  // skip copying '-'
            }
        }

        // Copy normal character or invalid range literally
        s2[j++] = s1[i];
    }

    s2[j] = '\0';
}

int main() {
    char s1[100], s2[500];
    printf("Enter shorthand string: ");
    fgets(s1, sizeof(s1), stdin);

    expand(s1, s2);

    printf("Expanded: %s\n", s2);
    return 0;
}

/*output
Enter shorthand string: a-b-c
abc

Enter shorthand string: a-z0-3
abcdefghijklmnopqrstuvwxyz0123

Enter shorthand string: -abc-
-abc-

Enter shorthand string: a-b-c
abc

Enter shorthand string: xyz-
xyz-

Enter shorthand string: x-z-
xyz-

Enter shorthand string: -a-c
-abc

Enter shorthand string: a-c0-3
abc0123

Enter shorthand string: 0-5
012345

Enter shorthand string: A-C
ABC

Enter shorthand string: a-d
abcd
*/
