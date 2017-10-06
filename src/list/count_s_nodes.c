/*
 * =====================================================================================
 *
 *       Filename:  count_s_nodes.c
 *
 *    Description:  Returns the value the length of the list
 *    			Parse Once.
 *
 *        Version:  1.0
 *        Created:  10/05/2017 01:15:39 PM
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

int count_s_nodes(struct s_node* head){
	if(!head)
		return 1;
	int i = 1;
	struct s_node* t = head;
	while(t->next){
		i++;
		t = t->next;
	}
	return i;
}
