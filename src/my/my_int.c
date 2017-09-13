#ifndef _MY_INT_
#define _MY_INT_
#include "my.h"
#include "helpers.h"

void my_int(int a){
	int num = a;
	int pow = 1;
	int len = 0;
	while(num/pow >= 10){
		pow *= 10;
		len++;
	}
	if(num<0){
		my_char('-');
	}
	for(int curCharInd=len; curCharInd>=0; curCharInd--){
		int curChar = num/pow;
		num -= curChar*pow;
		if(curChar<0)
			curChar = -curChar;
		pow/=10;
		my_char(curChar+'0');
	}
}
#endif
