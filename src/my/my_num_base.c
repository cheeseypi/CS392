#ifndef _MY_NUM_BASE_
#define _MY_NUM_BASE_
#include "my.h"

void my_num_base(int i, char* str){
	if(i<0){
		my_char('-');
	}
	if(str == NULL || str[0] == '\0'){
		my_str("Invalid base string");
		return;
	}
	else if(my_strlen(str) == 1){
		int num = i;
		if(i > 0)
			num = -1 * i;
		for(int ctr = 0; ctr>num; ctr--)
			my_char(str[0]);
		return;
	}
	int num = i;
	int newBase = my_strlen(str);
	int pow = 1;
	int len = 0;
	if(num<0)
		while(num/pow <= -newBase){
			pow *= newBase;
			len++;
		}
	else
		while(num/pow >= newBase){
			pow *= newBase;
			len++;
		}
	for(int curCharInd=len; curCharInd>=0; curCharInd--){
		int curChar = num / pow;
		num -= curChar*pow;
		if(curChar<0)
			curChar = -1 * curChar;
		pow/=newBase;
		my_char(str[curChar]);
	}
	return;
}
#endif

/*
 * Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System
 */
