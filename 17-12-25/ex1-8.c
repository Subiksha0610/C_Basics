#include<stdio.h>
main(){
int cb=0,ct=0,cnl=0;
int c;
while( (c=getchar()) !=EOF){
if(c==' ')
++cb;
else if(c=='\t')
++ct;
else if(c=='\n')
++cnl;
}
printf("No of Blanks: %d\n Number of Tabs: %d\n Number of NewLines: %d\n",
cb,ct,cnl);
}
