/*
 * =====================================================================================
 *
 *       Filename:  append.c
 *
 *    Description:  Adds a node to the end of a list. DO NOT add a NULL pointer or a
 *    			node with a NULL elem.
 *
 *        Version:  1.0
 *        Created:  09/25/2017 03:33:36 PM
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

void append(struct s_node* node, struct s_node** head){
	if(!node || !node->elem || !head)
		return;
	if(!*head)
		add_node(node,head);
	else{
		struct s_node* t = *head;
		while(t->next)
			t = t->next;
		t->next = node;
		node->prev = t;
	}
}
