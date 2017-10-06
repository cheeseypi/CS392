/*
 * =====================================================================================
 *
 *       Filename:  traverse_int.c
 *
 *    Description:  Prints all the elems as ints separated by a space
 *
 *        Version:  1.0
 *        Created:  10/02/2017 01:21:25 PM
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

void traverse_int(struct s_node* head){
	for(struct s_node* t = head; t; t = t->next){
		int* elemen = (int*) t->elem;
		my_int(*elemen);
		my_char(' ');
	}
	my_char('\n');
}
