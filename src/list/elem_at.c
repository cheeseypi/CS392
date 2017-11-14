/*
 * =====================================================================================
 *
 *       Filename:  elem_at.c
 *
 *    Description:  Returns a pointer to the elem at index n or the last node.
 *    			Parse once.
 *
 *        Version:  1.0
 *        Created:  10/05/2017 03:12:04 PM
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

void* elem_at(struct s_node* head, int n){
	if(head==NULL)
		return NULL;
	struct s_node* t = head;
	for(int ctr = 0; t->next && ctr<n; (ctr++, t = t->next));
	return t->elem;
}
