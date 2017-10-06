/*
 * =====================================================================================
 *
 *       Filename:  add_elem.c
 *
 *    Description:  Creates a new node with elem and adds it to head. DO NOT add a NULL
 *    			elem.
 *
 *        Version:  1.0
 *        Created:  09/25/2017 03:06:19 PM
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

void add_elem(void* elem, struct s_node** head){
	if(elem == NULL)
		return;
	add_node(new_node(elem,*head,NULL),head);
}
