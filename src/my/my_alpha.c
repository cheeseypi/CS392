#ifndef _MY_ALPHA_
#define _MY_ALPHA_
#include "my_char.c"
#include "my.h"
void my_alpha(){
	for(char aChar = 'A'; aChar<='Z'; aChar++)
		my_char(aChar);
}
#endif
