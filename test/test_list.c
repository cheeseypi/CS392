/*
	new_node X
	add_node X
	add_elem X
	append X
	add_node_at
	remove_node X
	remove_last X
	remove_node_at X
	count_s_nodes
	empty_list
	node_at
	elem_at
	traverse_int
	traverse_char
	traverse_string
	debug_int
	debug_char
	debug_string
	print_int
	print_char
	print_string
 */
#include "list.h"
void testInts(){
	int* nums = (int*) malloc(sizeof(int)*100);
	for(int i = 0; i<100; i++)
		nums[i]=i-50;
	struct s_node* head = new_node(&(nums[0]), NULL, NULL);
	for(int i = 1; i<100; i++)
		append(new_node(&(nums[i]), NULL, NULL),&head);
	traverse_int(head);
	debug_int(node_at(head,90));
	my_char('\n');
	int a = -100;
	add_elem(&a,&head);
	add_elem(NULL,&head);
	traverse_int(head);
	my_char('\n');
	struct s_node* newList = new_node(NULL, NULL, NULL);
	debug_int(newList);
	my_char('\n');
	remove_node(&head);
	traverse_int(head);
	remove_node(&head);
	traverse_int(head);
	remove_node(&head);
	traverse_int(head);
	my_char('\n');
	struct s_node* temp = node_at(head,4);
	remove_node(&temp);
	traverse_int(head);
	my_char('\n');
	add_node_at(new_node(&nums[53],NULL,NULL),&head,4);
	traverse_int(head);
	my_char('\n');
	remove_node_at(&head,4);
	traverse_int(head);
	my_char('\n');
	my_int(count_s_nodes(head));
	my_char('\n');
	my_char('\n');
	remove_last(&head);
	traverse_int(head);
}

void testChars(){

}

void testStrings(){

}

int main(){
	testInts();
	testChars();
	testStrings();
}
