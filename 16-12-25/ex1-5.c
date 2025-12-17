#include<stdio.h>
main(){
int fah;
float cel;
printf("Fahrenheit Celsius\n");
for(fah=300;fah>=0;fah=fah-20){
cel=5.0*(fah-32)/9.0;
printf("%3d %6.1f\n",fah,cel);
}
}

/* output 
Fahrenheit  Celsius
300    148.9
280    137.8
260    126.7
240    115.6
220    104.4
200     93.3
180     82.2
160     71.1
140     60.0
120     48.9
100     37.8
 80     26.7
 60      15.6
 40      4.4
 20      -6.7
  0      -17.8
*/
