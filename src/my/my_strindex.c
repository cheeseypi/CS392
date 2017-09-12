#ifndef _MY_STRINDEX_
#define _MY_STRINDEX_
#include "my.h"
int my_strindex(char* str, char fin){
	if(str == NULL)
		return -1;
	for(int i = 0; str[i]!='\0'; i++)
		if(str[i] == fin)
			return i;
	return -1;
}
#endif
