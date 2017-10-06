/*
 * =====================================================================================
 *
 *       Filename:  add_node.c
 *
 *    Description:  Inserts a node at the start of the list. DO NOT add a NULL pointer
 *    			or a node with a NULL elem. DOES NOT PARSE.
 *
 *        Version:  1.0
 *        Created:  09/22/2017 01:35:38 PM
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

void add_node(struct s_node* node, struct s_node** head){
	if(node == NULL || node->elem == NULL)
		return;
	node->next = *head;
	(*head)->prev = node;
	*head = node;
}
