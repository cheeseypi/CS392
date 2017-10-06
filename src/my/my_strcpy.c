#include "my.h"

char* my_strcpy(char* dst, char* src){
	if(src==NULL){
		dst[0]='\0';
		return dst;
	}
	for(int i = 0; i<=my_strlen(src); i++){
		dst[i] = src[i];
	}
	return dst;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
