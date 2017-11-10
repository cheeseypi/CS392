CC = gcc
CFLAGS = -std=c99 -I../../include/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = ../../lib

mylist_o = new_node.o add_node.o add_elem.o append.o add_node_at.o remove_node.o remove_last.o remove_node_at.o count_s_nodes.o empty_list.o node_at.o elem_at.o traverse_int.o traverse_char.o traverse_string.o debug_int.o debug_char.o debug_string.o print_int.o print_char.o print_string.o

mainprog_c = test.c

all: ../../lib/liblist.a

../../lib/liblist.a: $(mylist_o)
	ar -rc ../../lib/liblist.a $(mylist_o)
	ranlib ../../lib/liblist.a

test.out: ../../lib/libmy.a ../../lib/liblist.a
	$(CC) $(CFLAGS) -o test.out $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy -g

clean:
	rm -rf *.o

fclean: clean
	-rm -rf ../../lib/liblist.a
	-rm -rf ../../bin/main

re: fclean all

test: test.out
	-./test.out
	make fclean

valgrind: test.out
	-valgrind ./test.out
	make fclean

.SILENT:
