/*
 * =====================================================================================
 *
 *       Filename:  traverse_char.c
 *
 *    Description:  Prints all the elems as chars separated by a space
 *
 *        Version:  1.0
 *        Created:  10/02/2017 01:25:18 PM
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

void traverse_char(struct s_node* head){
	for(struct s_node* t = head; t; t = t->next){
		char* elemen = (char*) t->elem;
		my_char(*elemen);
		my_char(' ');
	}
	my_char('\n');
}
