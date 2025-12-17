#include<stdio.h>
int main(){
	int blank=0,tab=0,backslash=0;
	int c;

	while( (c=getchar())!=EOF){
		if(c=='\b'){
			printf("\\b");
		} else if(c=='\t'){
			printf("\\t");
		} else if(c=='\\'){
			printf("\\\\");
		} else{
			putchar(c);
		}
	}
return 0;
}
