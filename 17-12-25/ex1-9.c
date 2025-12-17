#include<stdio.h>
int main(){
int c;
int blank=0;
while( (c=getchar()) !=EOF){
if(c==' '){
if(!blank){
putchar(' ');
blank=1;
}
}
else{
putchar(c);
blank=0;
}
}
return 0;
}
