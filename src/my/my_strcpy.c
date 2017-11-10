#include "my.h"

char* my_strcpy(char* dst, char* src){
	if(src==NULL || dst==NULL){
		return dst;
	}
	int srclen = my_strlen(src);
	int i;
	for(i=0; i<=srclen; i++){
		dst[i] = src[i];
	}
	dst[i-1]='\0';
	return dst;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
