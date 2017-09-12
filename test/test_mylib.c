/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  temp file! testing libmy
 *
 *        Version:  1.0
 *        Created:  09/01/2017 01:01:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "my_str.c"
#include "my_int.c"
#include "my_strlen.c"
#include "my_alpha.c"
#include "my_digits.c"
#include "my_revstr.c"

#include <string.h>
#include <stdio.h>
int main(){
	my_str("Hello, World!\n");
	my_int(my_strlen("Hello, World!"));
	//Max printable int value 1410065407 -- TODO Figure out
	my_char('\n');
	for(int i=-10; i<=10; i++){
		my_int(i);
		my_char('\n');
	}
	my_alpha();
	my_char('\n');
	my_digits();
	my_char('\n');
	char* hello = (char*) malloc(sizeof(char)*15);
	strcpy(hello, "Hello, World!\0");
	my_str(hello);
	my_char('\n');
	my_revstr(hello);
	my_str(hello+'\n');
	printf("\n");
	printf(hello);
}
