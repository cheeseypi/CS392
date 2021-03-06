/*
 * =====================================================================================
 *
 *       Filename:  remove_node_at.c
 *
 *    Description:  Removes the node at index n or the last node.
 *    			Parse once
 *
 *        Version:  1.0
 *        Created:  10/05/2017 12:53:51 PM
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

void* remove_node_at(struct s_node** head, int n){
	if(head==NULL || *head==NULL)
		return NULL;
	struct s_node* t = *head;
	for(int ctr = 0; t->next!=NULL && ctr<n; ctr++)
		t = t->next;
	if(t->prev!=NULL)
		return remove_node(&t);
	return remove_node(head);
}

