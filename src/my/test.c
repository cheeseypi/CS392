/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/2017 02:13:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto (), mvd369@gmail.com
 *   Organization:  
 *                  I Pledge My Honor That I Have Abided By The Stevens Honor System
 *
 * =====================================================================================
 */
#include "my.h"

int main(){
	my_str("Hello, Wor");
	my_char('\n');
	my_str(my_strnconcat("Hello, ","World",3));
	my_char('\n');
	my_str("World");
	my_char('\n');
	my_str(my_strnconcat(NULL,"World",5));
	my_char('\n');
}
