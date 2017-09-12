#ifndef _MY_INT_
#define _MY_INT_
#include "my.h"
#include "helpers.h"

void my_int(int a){
	int num = a;
	if(num<0){
		num = -num;
		my_char('-');
	}
	for(int curCharInd=simple_intlen(num)-1; curCharInd>=0; curCharInd--){
		int curChar = num/simple_pow(10,curCharInd);
		num = num-curChar*simple_pow(10,curCharInd);
		my_char(curChar+'0');
	}
}
#endif
