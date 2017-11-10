#include "my.h"

int my_strcmp(char* a, char* b){
	return my_strncmp(a,b,my_strlen(a)+1);
}

/* Matthew Doto
 * I pledge my honor that I have abided by the Stevens Honor System */
