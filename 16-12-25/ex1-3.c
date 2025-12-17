#include <stdio.h>
main(){
float start, end, count;
start=0;
end=300;
count=20;
float cel, fah ;
fah=start;
printf("Fahrenheit Celsius\n");
while(fah<=end){
cel=(5.0/9.0) * (fah -32.0);
printf(" %3.0f %10.1f \n",fah,cel);
fah=fah+count;
}
} 

/* output
Fahrenheit Celsius
   0      -17.8
  20       -6.7
  40        4.4
  60       15.6
  80       26.7
 100       37.8
 120       48.9
 140       60.0
 160       71.1
 180       82.2
 200       93.3
 220      104.4
 240      115.6
 260      126.7
 280      137.8
 300      148.9
*/
