#include "my.h"

int min(int a, int b){
	if(a<b)
		return a;
	return b;
}

char* my_strnconcat(char* a, char* b, int n){
	if(a==NULL && b==NULL)
		return NULL;
	int alen,blen;
	if(a==NULL)
		alen=0;
	else
		alen=my_strlen(a);
	if(b==NULL)
		blen=0;
	else
		blen=my_strlen(b);
	int n1 = n;
	if(n<0)
		n1=0;
	int newLen = alen + min(blen,n1);
	char* newStr = (char*) malloc(sizeof(char)*(newLen+1));
	if(a==NULL)
		my_strcpy(newStr,"");
	else
		my_strcpy(newStr,a);
	if(b==NULL)
		my_strcpy(newStr+alen,"\0");
	else
		my_strncpy(newStr+alen,b,min(blen,n1));
	return newStr;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
