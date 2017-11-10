/*
 * =====================================================================================
 *
 *       Filename:  empty_list.c
 *
 *    Description:  Frees all the nodes in the list.
 *    			CHALLENGE: Write in two lines (allowed to use other methods in this
 *    			assignment)
 *
 *        Version:  1.0
 *        Created:  10/05/2017 01:40:58 PM
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

void empty_list(struct s_node** head){
	if(head)
		while(count_s_nodes(*head)>0 && *head)
			remove_node(head);
}
