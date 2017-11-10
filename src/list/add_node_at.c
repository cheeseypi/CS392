/*
 * =====================================================================================
 *
 *       Filename:  add_node_at.c
 *
 *    Description:  Adds a node at index n of a list or at the end of the list if n is
 *    			too large.
 *
 *        Version:  1.0
 *        Created:  09/26/2017 03:10:49 PM
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

void add_node_at(struct s_node* node, struct s_node** head, int n){
	if(node == NULL || node->elem == NULL || head == NULL || n<0)
		return;
	if(!*head){
		add_node(node,head);
		return;
	}
	struct s_node* t = *head;
	int ctr = 0;
	while(t->next && ctr<n){
		t = t->next;
		ctr++;
	}
	if(ctr==n){
		node->next = t;
		node->prev = t->prev;
		if(t->prev)
			t->prev->next = node;
	}
	else{
		t->next=node;
		node->prev=t;
	}
	if(node->next)
		node->next->prev=node;
}
