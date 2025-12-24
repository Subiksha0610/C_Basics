/*Write a function escape(s,t) that converts characters like newline and tab 
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.Write 
a function for the other direction as well, converting escape sequences into the real characters. */
#include <stdio.h>

void escape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

int main() {
    char t[100], s[200];
    printf("Enter a string: ");
    fgets(t, sizeof(t), stdin);
    escape(s, t);
    printf("Escaped: %s\n", s);
    return 0;
}
/*output
Enter a string: hello           world
Escaped: hello\t\tworld\n
*/