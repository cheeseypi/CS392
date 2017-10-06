/*
 * =====================================================================================
 *
 *       Filename:  print_char.c
 *
 *    Description:  Prints the elem of node as a char
 *
 *        Version:  1.0
 *        Created:  10/02/2017 02:02:41 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Doto (), mvd369@gmail.com
 *   Organization:  
 *                  I Pledge My Honor That I Have Abided By The Stevens Honor System
 *
 * =====================================================================================
 */
#include "list.h"

void print_char(struct s_node* node){
	if(node && node->elem){
		my_char(*((char*)node->elem));
	}
	else
		my_str("NULL");
}
