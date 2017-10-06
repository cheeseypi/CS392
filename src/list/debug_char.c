/*
 * =====================================================================================
 *
 *       Filename:  debug_char.c
 *
 *    Description:  Prints all the elems as chars separated by a space in the format
 *    			(NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL)
 *
 *        Version:  1.0
 *        Created:  10/02/2017 01:44:51 PM
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

void debug_pr_char(struct s_node* node){
	my_char('(');
	if(node->prev && node->prev->elem){
		my_char(*((char*)node->prev->elem));
	}
	else{
		my_str("NULL");
	}
	my_str(" <- ");
	if(node->elem){
		my_char(*((char*)node->elem));
	}
	else{
		my_str("NULL");
	}
	my_str(" -> ");
	if(node->next && node->next->elem){
		my_char(*((char*)node->next->elem));
	}
	else{
		my_str("NULL");
	}
	my_char(')');
}

void debug_char(struct s_node* head){
	for(struct s_node* t = head; t; t = t->next){
		debug_pr_char(t);
		my_str(", ");
	}
	my_char('\n');
}
