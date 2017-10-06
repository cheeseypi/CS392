/*
 * =====================================================================================
 *
 *       Filename:  debug_string.c
 *
 *    Description:  Prints all the elems as strings separated by a space in the format
 *    			(NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL)
 *
 *        Version:  1.0
 *        Created:  10/02/2017 01:51:07 PM
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

void debug_pr_string(struct s_node* node){
	my_char('(');
	if(node->prev && node->prev->elem){
		my_str((char*)node->prev->elem);
	}
	else{
		my_str("NULL");
	}
	my_str(" <- ");
	if(node->elem){
		my_str((char*)node->elem);
	}
	else{
		my_str("NULL");
	}
	my_str(" -> ");
	if(node->next && node->next->elem){
		my_str((char*)node->next->elem);
	}
	else{
		my_str("NULL");
	}
	my_char(')');
}

void debug_string(struct s_node* head){
	for(struct s_node* t = head; t; t = t->next){
		debug_pr_string(t);
		my_str(", ");
	}
	my_char('\n');
}
