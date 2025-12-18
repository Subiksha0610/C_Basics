#include <stdio.h>

#define IN  1
#define OUT 0
int main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("Number of line:%d\n Number of Words:%d\n Number of Character: %d\n", nl, nw, nc);
return 0;
}

/* output
Hello world\n
Number of line:1
 Number of Words:2
 Number of Character: 14

Hello world\tagain\n
Number of line:1
 Number of Words:2
 Number of Character: 21

//empty 
Number of line:1
 Number of Words:0
 Number of Character: 1

Number of line:0
 Number of Words:0
 Number of Character: 0

Hello\nworld
Number of line:1
 Number of Words:1
 Number of Character: 13

Hello, world!\n
Number of line:1
 Number of Words:2
 Number of Character: 16
*/
