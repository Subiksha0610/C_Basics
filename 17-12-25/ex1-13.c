#include <stdio.h>

#define IN  1
#define OUT 0

int main() {
    int c, state, length;
    int ndigit[20];

    for (int i = 0; i < 20; i++)
        ndigit[i] = 0;

    state = OUT;
    length = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                if (length < 20)
                    ++ndigit[length];
                length = 0;
                state = OUT;
            }
        } else {
            state = IN;
            ++length;
        }
    }

    for (int i = 1; i < 20; i++) {
	if(ndigit[i]>0){
        	printf("%2d: ", i);
        	for (int j = 0; j < ndigit[i]; j++)
            		putchar('*');
        		putchar('\n');
    }}

    return 0;
}
