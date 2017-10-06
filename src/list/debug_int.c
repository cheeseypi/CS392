/*
 * =====================================================================================
 *
 *       Filename:  debug_int.c
 *
 *    Description:  Prints all the elems as ints separated by a space in the format
 *    			(NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL)
 *
 *        Version:  1.0
 *        Created:  10/02/2017 01:29:07 PM
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

void debug_pr_int(struct s_node* node){
	my_char('(');
	if(node->prev && node->prev->elem){
		my_int(*((int*)node->prev->elem));
	}
	else{
		my_str("NULL");
	}
	my_str(" <- ");
	if(node->elem){
		my_int(*((int*)node->elem));
	}
	else{
		my_str("NULL");
	}
	my_str(" -> ");
	if(node->next && node->next->elem){
		my_int(*((int*)node->next->elem));
	}
	else{
		my_str("NULL");
	}
	my_char(')');
}

void debug_int(struct s_node* head){
	for(struct s_node* t = head; t; t = t->next){
		debug_pr_int(t);
		my_str(", ");
	}
	my_char('\n');
}
