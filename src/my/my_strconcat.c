#include "my.h"
char* my_strconcat(char* a, char* b){
	int newLen = my_strlen(a) + my_strlen(b);
	char* newStr = (char*) malloc(sizeof(char)*(newLen+1));
	my_strcpy(newStr,a);
	my_strcat(newStr,b);
	return newStr;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
