/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  Testing libmy
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
#include "my.h"

#include <limits.h>
#include <string.h>
#include <stdio.h>

void test_my_alpha(){
	my_alpha();
}
void test_my_digits(){
	my_digits();
}
void test_my_int(){
	for(int i=-100; i<=100; i++){
		my_int(i);
		my_str(", ");
	}
	my_char('\n');
	my_int(INT_MIN);
	my_char('\n');
	my_int(INT_MAX);
}
void test_my_num_base(){
	my_str("-BA: ");
	my_num_base(-4,"ABCD");
	my_char('\n');
	my_str("Error: ");
	my_num_base(4,"");
	my_char('\n');
	my_str("Error: ");
	my_num_base(4,NULL);
	my_char('\n');
	my_str("B: ");
	my_num_base(11,"0123456789ABCDEF");
	my_char('\n');
	my_str("-15: ");
	my_num_base(-21,"0123456789ABCDEF");
	my_char('\n');
	my_str("14: ");
	my_num_base(11,"0123456");
	my_char('\n');
	my_str("11111111111: ");
	my_num_base(11,"1");
	my_char('\n');
	my_str("0: ");
	my_num_base(0,"01");
	my_char('\n');
	my_str("301: ");
	my_num_base(433,"0123456789XE");
	my_char('\n');
	my_str("-4BB2308A8: ");
	my_num_base(INT_MIN,"0123456789AB");
	my_char('\n');
	my_str("4BB2308A7: ");
	my_num_base(INT_MAX,"0123456789AB");
}
void test_my_revstr(){
	char* hello = (char*) malloc(sizeof(char)*15);
	strcpy(hello, "Hello, World!");
	my_revstr(hello);
	my_str(hello);
	my_char('\n');
	strcpy(hello, "Nascar");
	my_revstr(hello);
	my_str(hello);
	my_char('\n');
	strcpy(hello, "Theearthisflat");
	my_revstr(hello);
	my_str(hello);
	strcpy(hello,"              ");
	free(hello);
	my_revstr(NULL);
}
void test_my_str(){
	char* hello = (char*) malloc(sizeof(char)*15);
	strcpy(hello, "Hello, World!");
	my_str(hello);
	my_char('\n');
	strcpy(hello, "Nascar");
	my_str(hello);
	my_char('\n');
	strcpy(hello, "Theearthisflat");
	my_str(hello);
	my_char('\n');
	strcpy(hello,"              ");
	free(hello);
	my_str(NULL);
}
void test_my_strindex(){
	char* hello = (char*) malloc(sizeof(char)*15);
	strcpy(hello, "Hello, World!");
	my_int(my_strindex(hello,'l'));
	my_char('\n');
	strcpy(hello, "Nascar");
	my_int(my_strindex(hello,'c'));
	my_char('\n');
	strcpy(hello, "Theearthisflat");
	my_int(my_strindex(hello,'t'));
	my_char('\n');
	strcpy(hello,"              ");
	free(hello);
	my_int(my_strindex(NULL,'t'));
	my_char('\n');
	my_int(my_strindex("",'t'));
}
void test_my_strlen(){
	my_int(my_strlen("Hello, World!"));
}
void test_my_strrindex(){
	char* hello = (char*) malloc(sizeof(char)*15);
	strcpy(hello, "Hello, World!");
	my_int(my_strrindex(hello,'l'));
	strcpy(hello,"              ");
	free(hello);
}
int main(){
	test_my_alpha();my_char('\n');
	test_my_digits();my_char('\n');
	test_my_int();my_char('\n');
	test_my_num_base();my_char('\n');
	test_my_str();my_char('\n');
	test_my_revstr();my_char('\n');
	test_my_strindex();my_char('\n');
	test_my_strlen();my_char('\n');
	test_my_strrindex();my_char('\n');
	//HELLO
}
