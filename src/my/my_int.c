#ifndef _MY_INT_
#define _MY_INT_
#include "my.h"

void my_int(int a){
	int num = a;
	int pow = 1;
	int len = 0;
	if(num<0)
		while(num/pow <= -10){
			pow *= 10;
			len++;
		}
	else
		while(num/pow >= 10){
			pow *= 10;
			len++;
		}
	if(num<0){
		my_char('-');
	}
	for(int curCharInd=len; curCharInd>=0; curCharInd--){
		int curChar = num / pow;
		num -= curChar * pow;
		if(curChar<0)
			curChar = -1 * curChar;
		pow/=10;
		my_char(curChar+'0');
	}
}
#endif

/*
 * Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System
 */
