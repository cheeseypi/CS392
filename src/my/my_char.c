/*
 * =====================================================================================
 *
 *       Filename:  my_char.c
 *
 *    Description:  My_Char
 *
 *        Version:  1.0
 *        Created:  09/11/2017 12:47:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _MY_CHAR_
#define _MY_CHAR_
#include "my.h"

void my_char(char c){
	write(1,&c,1);
}
#endif
