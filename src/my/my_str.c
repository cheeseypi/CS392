#ifndef _MY_STR_
#define _MY_STR_
#include "my.h"
#include "my_char.c"

void my_str(char* str){
	if(str == NULL)
		return;
	int i = 0;
	while(str[i]!='\0'){
		my_char(str[i]);
		i++;
	}
}
#endif
