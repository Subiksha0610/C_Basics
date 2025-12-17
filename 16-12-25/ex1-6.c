#include<stdio.h>
main(){
int c;
while( (c=getchar()) != EOF){
printf("\nEOF Result: 1\n");
}
printf("Reached EOF: %d\n",(c!=EOF));
}

/*output
h
Result: 1
Result: 1
b
Result: 1
Result: 1
h
Result: 1
Result: 1
u
Result: 1
Result: 1
Reached EOF: 0
*/
