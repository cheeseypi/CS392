#ifndef _MY_REVSTR_
#define _MY_REVSTR_
#include "my.h"
int my_revstr(char* str){
	if(str == NULL)
		return -1;
	int len = my_strlen(str);
	for(int i = 0; i < len/2; i++){
		char temp = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = temp;
	}
	return len;
}
#endif

/*
 * Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System
 */
