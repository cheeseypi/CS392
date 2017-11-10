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
	if(!node || !*node)
		return NULL;
	struct s_node* oldNode = *node;
	void* elem = oldNode->elem;
	if(oldNode->next)
		oldNode->next->prev=oldNode->prev;
	if(oldNode->prev)
		oldNode->prev->next=oldNode->next;
	else
		*node = oldNode->next;
	oldNode->next=NULL;
	oldNode->prev=NULL;
	oldNode->elem=NULL;
	free(oldNode);
	return elem;
}
