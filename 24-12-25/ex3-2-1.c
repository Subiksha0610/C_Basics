/*Write a function escape(s,t) that converts characters like newline and tab 
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.Write 
a function for the other direction as well, converting escape sequences into the real characters. */
#include <stdio.h>

void unescape(char s[], char t[]) {
    int i = 0, j = 0;

    while (t[i] != '\0') {

        if (t[i] == '\\') {

          
            if (t[i + 1] == '\0') {
                s[j++] = '\\';
                break;
            }

            i++;  

            switch (t[i]) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                case '\\':
                    s[j++] = '\\';
                    break;
                default:
                  
                    s[j++] = '\\';
                    s[j++] = t[i];
                    break;
            }
        } 
        else {
            s[j++] = t[i];
        }

        i++;
    }

    s[j] = '\0';
}

int main(void) {
    char t[200], s[200];

    printf("Enter a string with escape sequences: ");
    fgets(t, sizeof(t), stdin);

    unescape(s, t);

    printf("Unescaped output:\n%s", s);

    return 0;
}

/*output
Enter a string with escape sequences: Hello\t\tworld\n
Unescaped:
Hello           world

*/