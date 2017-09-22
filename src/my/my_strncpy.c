#include "my.h"

char* my_strncpy(char* dst, char* src, int n){
	if(src==NULL && n>0)
		dst[0]='\0';
	for(int i = 0; i<=my_strlen(src) && i<n; i++){
		dst[i] = src[i];
	}
	return dst;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
