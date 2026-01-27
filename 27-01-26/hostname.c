#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     
#include <string.h>

#define HOSTNAME_MAX 256  

int main(void) {
    char hostname[HOSTNAME_MAX];

    
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
        exit(1);
    }

    printf("My hostname is: %s\n", hostname);

    return 0;
}
/*output
subiksha@DESKTOP-CBQDRR5:~/27-01-26$ gcc hostname.c -o hostname
subiksha@DESKTOP-CBQDRR5:~/27-01-26$ ./hostname
My hostname is: DESKTOP-CBQDRR5
*/