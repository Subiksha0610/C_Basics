#include <stdio.h>

int main() {
    int c;
    int freq[128];

    for (int i = 0; i < 128; i++)
        freq[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c < 128)
            ++freq[c];
    }

    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            printf("%c: ", i);
            for (int j = 0; j < freq[i]; j++)
                putchar('*');
            putchar('\n');
        }
    }

    return 0;
}

/*output 
abaac

: *
a: ***
b: *
c: *

abaac

: *
 : *
a: ***
b: *
c: *

ghyyujjjjkgtyfrrdgj

: *
d: *
f: *
g: ***
h: *
j: *****
k: *
r: **
t: *
u: *
y: ***
*/
