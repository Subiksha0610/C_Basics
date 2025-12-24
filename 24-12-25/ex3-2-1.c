/*Write a function escape(s,t) that converts characters like newline and tab 
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.Write 
a function for the other direction as well, converting escape sequences into the real characters. */
#include <stdio.h>

void unescape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; i++) {
        if (t[i] == '\\') {
            i++;
            switch (t[i]) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                default:
                    s[j++] = t[i];
                    break;
            }
        } else {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}

int main() {
    char t[200], s[200];
    printf("Enter a string with escape sequences: ");
    fgets(t, sizeof(t), stdin);
    unescape(s, t);
    printf("Unescaped:\n%s", s);
    return 0;
}
/*output
Enter a string with escape sequences: Hello\t\tworld\n
Unescaped:
Hello           world

*/