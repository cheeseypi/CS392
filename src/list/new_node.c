/*
 * =====================================================================================
 *
 *       Filename:  new_node.c
 *
 *    Description:  Allocates and returns a new node with the given pointers. You may
 *    			create nodes with NULLs.
 *
 *        Version:  1.0
 *        Created:  09/22/2017 01:31:07 PM
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

struct s_node* new_node(void* elem, struct s_node* next, struct s_node* previous){
	struct s_node* rT = (struct s_node*) malloc(sizeof(struct s_node));
	rT->elem = elem;
	rT->next = next;
	rT->prev = previous;
	return rT;
}
