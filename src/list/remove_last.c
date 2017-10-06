/*
 * =====================================================================================
 *
 *       Filename:  remove_last.c
 *
 *    Description:  Removes the last node from the list.
 *    			Parse Once.
 *
 *        Version:  1.0
 *        Created:  10/05/2017 12:49:46 PM
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

void* remove_last(struct s_node** head){
	return remove_node_at(head,count_s_nodes(*head)-1);
}
