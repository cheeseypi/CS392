#include "my.h"

int min(int a, int b){
	if(a<b)
		return a;
	return b;
}

char* my_strnconcat(char* a, char* b, int n){
	int newLen = my_strlen(a) + min(my_strlen(b),n);
	char* newStr = (char*) malloc(sizeof(char)*(newLen+1));
	my_strcpy(newStr,a);
	my_strncpy(newStr+my_strlen(a),b,min(my_strlen(b),n));
	return newStr;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
