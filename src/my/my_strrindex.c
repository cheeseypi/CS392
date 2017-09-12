#ifndef _MY_STRRINDEX_
#define _MY_STRRINDEX_
#include "my.h"
#include "my_strlen.c"
int my_strrindex(char* str, char fin){
	for(int i = my_strlen(str) - 1; i>=0; i--)
		if(str[i] == fin)
			return i;
	return -1;
}
#endif
