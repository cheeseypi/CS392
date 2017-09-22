#include "my.h"

int my_strncmp(char* a, char* b, int n){
	int a_val = 0;
	int b_val = 0;
	if(a==NULL)
		a_val=-1;
	if(b==NULL)
		b_val=-1;
	for(int ctr = 0; ctr<my_strlen(a) && ctr<n; ctr++)
		a_val+=a[ctr];
	for(int ctr = 0; ctr<my_strlen(b) && ctr<n; ctr++)
		b_val+=b[ctr];
	return a_val-b_val;
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
