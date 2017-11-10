#include "my.h"
char* my_strdup(char* str){
	if(str==NULL)
		return NULL;
	int len = my_strlen(str);
	char* newStr = (char*) malloc(sizeof(char)*(len+1));
	for(int i = 0; i < len; i++){
		newStr[i] = str[i];
	}
	newStr[len] = '\0';
	return newStr;
}
/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
