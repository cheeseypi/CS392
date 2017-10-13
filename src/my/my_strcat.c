#include "my.h"

char* my_strcat(char* dst, char* src){
	if(src==NULL || dst==NULL)
		return dst;
	int lendst = my_strlen(dst);
	return my_strcpy(dst+lendst, src)-(lendst);
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
