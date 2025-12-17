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

/* output 
\t
\n



\n
\n
\n
\t
\t
\t

t
y

j
m
 m
No of Blanks: 7
 Number of Tabs: 0
 Number of NewLines: 18



No of Blanks: 0
 Number of Tabs: 2
 Number of NewLines: 2
  */
