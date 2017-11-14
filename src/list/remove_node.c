/*
 * =====================================================================================
 *
 *       Filename:  remove_node.c
 *
 *    Description:  Removes the given node from the list. Returns elem and frees the
 *    			node from memory.
 *    			DOES NOT PARSE.
 *
 *        Version:  1.0
 *        Created:  10/05/2017 12:07:29 PM
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

void* remove_node(struct s_node** node){
	if(node==NULL || *node==NULL)
		return NULL;
	struct s_node* oldNode = *node;
	void* elem = oldNode->elem;
	if(oldNode->next!=NULL)
		oldNode->next->prev=oldNode->prev;
	if(oldNode->prev!=NULL)
		oldNode->prev->next=oldNode->next;
	*node = oldNode->next;
	free(oldNode);
	return elem;
}
