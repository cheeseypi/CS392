#include "my.h"

char* my_strncpy(char* dst, char* src, int n){
	if(src==NULL || dst==NULL)
		return dst;
	int i = 0;
	for(; i<=my_strlen(src) && i<n; i++){
		dst[i] = src[i];
	}
//	if(i>=n)
//		dst[i] = '\0';
	return dst;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
