#include "my.h"

char* my_strrfind(char* str, char tgt){
	int ind = my_strrindex(str, tgt);
	if(ind < 0)
		return NULL;
	return (str+ind);
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
