#include <stdio.h>
main(){
printf("Hello, World\n");
printf("Hello, World\t");
printf("Hello, World\\");
printf("Hello, \"World\"");
}

/* unknown escape sequence 
\q - warning: unknown escape sequence \q
\z - warning: unknown escape sequence \z
*/

/*output
Hello, World
Hello, World    Hello, World\Hello, "World"
*/
