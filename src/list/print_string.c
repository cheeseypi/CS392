/*
 * =====================================================================================
 *
 *       Filename:  print_string.c
 *
 *    Description:  Prints the elem of node as a string
 *
 *        Version:  1.0
 *        Created:  10/02/2017 02:04:02 PM
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
		my_str((char*)node->elem);
	}
	else
		my_str(NULL);
}
