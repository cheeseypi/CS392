#include "my.h"

int my_strncmp(char* a, char* b, int n){
	if(a==NULL && b==NULL)
		return 0;
	else if(a==NULL)
		return -2;
	else if(b==NULL)
		return 2;
	for(int ctr=0; ctr<n; ctr++){
		if(a[ctr]=='\0' && b[ctr]!='\0')
			return -3;
		else if(a[ctr]!='\0' && b[ctr]=='\0')
			return 3;
		else if(a[ctr]=='\0' && b[ctr]=='\0')
			return 0;
		if(a[ctr]<b[ctr])
			return -1;
		if(a[ctr]>b[ctr])
			return 1;
	}
	return 0;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
