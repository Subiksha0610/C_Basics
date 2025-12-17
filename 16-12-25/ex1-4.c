#include <stdio.h>
main(){
int start,end,count;
int fah,cel;
start=0;
end=300;
count=20;
cel=start;
printf("Celsius Fahrenheit\n");
while(cel<=end){
fah=(9/5 *cel) +32;
printf("%3d        %3d\n",cel,fah);
cel=cel+count;
}
}

/* output
Celsius Fahrenheit
  0         32
 20         52
 40         72
 60         92
 80        112
100        132
120        152
140        172
160        192
180        212
200        232
220        252
240        272
260        292
280        312
300        332
*/
