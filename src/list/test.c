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

typedef struct s_node* node;

void testInts(){
	int* nums = (int*) malloc(sizeof(int)*100);
	for(int i = 0; i<100; i++)
		nums[i]=i-50;

	my_str("add_node\n");
	node head = NULL;
	for(int i=-5;i<=5;i++)
		add_node(new_node(&(nums[i+50]),NULL,NULL),&head);
	my_str("5 4 3 2 1 0 -1 -2 -3 -4 -5\n");
	traverse_int(head);
	my_str("---\n");
	my_str("add_node_at\n");
	add_node_at(new_node(&(nums[9+50]),NULL,NULL),&head,1);
	add_node_at(new_node(&(nums[9+50]),NULL,NULL),&head,5);
	add_node_at(new_node(&(nums[9+50]),NULL,NULL),&head,420);
	my_str("5 9 4 3 2 9 1 0 -1 -2 -3 -4 -5 9\n");
	traverse_int(head);
	my_str("---\n");
	my_str("add_elem\n");
	add_elem(&(nums[10+50]),&head);
	add_elem(&(nums[11+50]),&head);
	add_elem(&(nums[12+50]),&head);
	my_str("12 11 10 5 9 4 3 2 9 1 0 -1 -2 -3 -4 -5 9\n");
	traverse_int(head);
	my_str("---\n");
	my_str("count_s_nodes\n");
	my_str("17\n");
	my_int(count_s_nodes(head));
	my_char('\n');
	my_str("---\n");
	my_str("append\n");
	append(new_node(&(nums[10+50]),NULL,NULL),&head);
	append(new_node(&(nums[11+50]),NULL,NULL),&head);
	append(new_node(&(nums[12+50]),NULL,NULL),&head);
	my_str("12 11 10 5 9 4 3 2 9 1 0 -1 -2 -3 -4 -5 9 10 11 12\n");
	traverse_int(head);
	my_str("---\n");
	my_str("remove_node\n");
	remove_node(&(head->next));
	remove_node(&(head->next->next));
	my_str("12 10 9 4 3 2 9 1 0 -1 -2 -3 -4 -5 9 10 11 12\n");
	traverse_int(head);
	my_str("---\n");
	my_str("remove_last\n");
	remove_last(&head);
	remove_last(&head);
	my_str("12 10 9 4 3 2 9 1 0 -1 -2 -3 -4 -5 9 10\n");
	traverse_int(head);
	my_str("---\n");
	my_str("count_s_nodes\n");
	my_str("16\n");
	my_int(count_s_nodes(head));
	my_char('\n');
	my_str("---\n");
	my_str("remove_node_at\n");
	remove_node_at(&head,1);
	remove_node_at(&head,5);
	remove_node_at(&head,420);
	my_str("12 9 4 3 2 1 0 -1 -2 -3 -4 -5 9\n");
	traverse_int(head);
	my_str("---\n");
	my_str("count_s_nodes\n");
	my_str("13\n");
	my_int(count_s_nodes(head));
	my_char('\n');
	my_str("---\n");
	my_str("empty_list\n");
	my_str("\n");
	empty_list(&head);
	traverse_int(head);
	my_str("---\n");
}

void testChars(){

}

void testStrings(){

}

int main(){
	testInts();
//	testChars();
//	testStrings();
}
