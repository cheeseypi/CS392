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
	if(node == NULL || node->elem == NULL || head == NULL || *head == NULL)
		return;
	struct s_node* t = *head;
	int ctr = 1;
	while(t->next && ctr<n){
		t = t->next;
		ctr++;
	}
	node->next = t->next;
	if(t->next != NULL)
		t->next->prev = node;
	node->prev = t;
	t->next = node;
}
