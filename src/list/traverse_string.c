/*
 * =====================================================================================
 *
 *       Filename:  traverse_string.c
 *
 *    Description:  Prints all the elems as strings separated by a space
 *
 *        Version:  1.0
 *        Created:  10/02/2017 01:26:57 PM
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

void traverse_string(struct s_node* head){
	for(struct s_node* t = head; t; t = t->next){
		char* elemen = (char*) t->elem;
		my_str(elemen);
		my_char(' ');
	}
	my_char('\n');
}
