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
	if(!node)
		return NULL;
	if((*node)->next)
		(*node)->next->prev = (*node)->prev;
	if(!(*node)->prev){
		//HEAD Behavior
		struct s_node* new_head = (*node)->next;
		void* elem = (*node)->elem;
		free(*node);
		*node = new_head;
		return elem;
	}
	(*node)->prev->next = (*node)->next;
	void* elem = (*node)->elem;
	free(*node);
	return elem;
}
