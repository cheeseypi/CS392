#include "my.h"

void my_str(char* str){
	if(str == NULL)
		return;
	int i = 0;
	while(str[i]!='\0'){
		my_char(str[i]);
		i++;
	}
}

/*
 * Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System
 */
