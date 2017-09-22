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
#include <assert.h>

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
void test_my_strfind(){
	my_str(my_strfind("Hello, World!",'W'));my_char('\n');
	my_str(my_strfind("Hello, World!",'Z'));my_char('\n');
	my_str(my_strfind("Hello, World!",'H'));my_char('\n');
	my_str(my_strfind("Hello, World!",' '));my_char('\n');
	my_str(my_strfind("Hello, World!",'l'));my_char('\n');
	my_str(my_strfind(NULL,'\0'));my_char('\n');
}
void test_my_strrfind(){
	my_str(my_strrfind("Hello, World!",'l'));my_char('\n');
	my_str(my_strrfind("Hello, World!",'o'));my_char('\n');
	my_str(my_strrfind("Hello, World!",'!'));my_char('\n');
	my_str(my_strrfind(NULL,'\0'));my_char('\n');
}
void test_my_strcmp(){
	assert(my_strcmp("aaa","zzz")<0);
	assert(my_strcmp("zzz","aaa")>0);
	assert(my_strcmp(NULL,"000")<0);
	assert(my_strcmp("000",NULL)>0);
	assert(my_strcmp(NULL,NULL)==0);
	assert(my_strcmp(NULL,"")<0);
	assert(my_strcmp("",NULL)>0);
	assert(my_strcmp("jjksn","jjksn")==0);
}
void test_my_strncmp(){
	assert(my_strncmp("aaa","zzz",100)<0);
	assert(my_strncmp("zzz","aaa",100)>0);
	assert(my_strncmp(NULL,"000",100)<0);
	assert(my_strncmp("000",NULL,100)>0);
	assert(my_strncmp(NULL,NULL,100)==0);
	assert(my_strncmp(NULL,"",100)<0);
	assert(my_strncmp("",NULL,100)>0);
	assert(my_strncmp("jjksn","jjksn",100)==0);
	assert(my_strncmp("aaaaaazzz","aaaaaaaaa",6)==0);
	assert(my_strncmp("zzzzzz","zazzzzzzzzz",4)>0);
	assert(my_strncmp("A","a",0)==0);
	assert(my_strncmp("Hello","World",100)<0);
}
void test_my_strcpy(){
	char* garbage = (char*) malloc(sizeof(char)*100);
	assert(my_strcmp(my_strcpy(garbage,"Hello, World!"),"Hello, World!")==0);
	assert(my_strcmp(my_strcpy(garbage,"\0"),"")==0);
	assert(my_strcmp(my_strcpy(garbage,""),"")==0);
	assert(my_strcmp(my_strcpy(garbage,"Nothing"),"Nothing")==0);
	my_strcpy(garbage,"          \0");
	free(garbage);
}
void test_my_strncpy(){
	char* garbage = (char*) malloc(sizeof(char)*100);
	my_strcpy(garbage,"            \0");
	assert(my_strcmp(my_strncpy(garbage,"Hello, World!",5),"Hello       ")==0);
	assert(my_strcmp(my_strncpy(garbage,"\0",1),"")==0);
	assert(my_strcmp(my_strncpy(garbage,"",1),"")==0);
	assert(my_strcmp(my_strncpy(garbage,"Nothing",6),"Nothin      ")==0);
	my_strcpy(garbage,"          \0");
	free(garbage);
}
void test_my_strcat(){
	char* garbage = (char*) malloc(sizeof(char)*100);
	my_strcpy(garbage,"Hello,");
	assert(my_strcmp(my_strcat(garbage," World!"),"Hello, World!")==0);
	my_strcpy(garbage,"                   \0");
	free(garbage);
}
void test_my_strdup(){
	assert(my_strcmp(my_strdup("Hello, World!"),"Hello, World!")==0);
	assert(my_strcmp(my_strdup(""),"")==0);
	assert(my_strcmp(my_strdup(NULL),"")==0);
}
void test_my_strconcat(){
	assert(my_strcmp(my_strconcat("Hello,"," World!"),"Hello, World!")==0);
	assert(my_strcmp(my_strconcat("Hello,",NULL),"Hello,")==0);
	assert(my_strcmp(my_strconcat(NULL," World!")," World!")==0);
}
void test_my_strnconcat(){
	assert(my_strcmp(my_strnconcat("Hello,"," World!",7),"Hello, World!")==0);
	assert(my_strcmp(my_strnconcat("Hello,",NULL,1),"Hello,")==0);
	assert(my_strcmp(my_strnconcat(NULL," World!",7)," World!")==0);
}
void test_my_atoi(){
	assert(my_atoi("123")==123);
	assert(my_atoi("123abc")==123);
	assert(my_atoi("2147483647")==INT_MAX);
	assert(my_atoi("-2147483648")==INT_MIN);
	assert(my_atoi("-123")==-123);
	assert(my_atoi("abc123abc")==123);
	assert(my_atoi("-abc123abc")==-123);
}
void test_pt1(){
	test_my_alpha();my_char('\n');
	test_my_digits();my_char('\n');
	test_my_int();my_char('\n');
	test_my_num_base();my_char('\n');
	test_my_str();my_char('\n');
	test_my_revstr();my_char('\n');
	test_my_strindex();my_char('\n');
	test_my_strlen();my_char('\n');
	test_my_strrindex();my_char('\n');
}
void test_pt2(){
	test_my_strfind();
	test_my_strrfind();
	test_my_strcmp();
	test_my_strncmp();
	test_my_strcpy();
	test_my_strncpy();
	test_my_strcat();
	test_my_strdup();
	test_my_strconcat();
	test_my_strnconcat();
	test_my_atoi();
}
int main(){
//	test_pt1();
	test_pt2();
	return 0;
}
