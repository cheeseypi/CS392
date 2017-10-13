CC = gcc
CFLAGS = -std=c99 -I../../include/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = ../../lib

mylist_o = new_node.o add_node.o add_elem.o append.o add_node_at.o remove_node.o remove_last.o remove_node_at.o count_s_nodes.o empty_list.o node_at.o elem_at.o traverse_int.o traverse_char.o traverse_string.o debug_int.o debug_char.o debug_string.o print_int.o print_char.o print_string.o

mainprog_c = ../../test/test_list.c

all: ../../lib/liblist.a

../../lib/liblist.a: $(mylist_o)
	ar -rc ../../lib/liblist.a $(mylist_o)
	ranlib ../../lib/liblist.a

../../bin/main: ../../lib/libmy.a ../../lib/liblist.a
	$(CC) $(CFLAGS) -o ../../bin/main $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy

clean:
	rm -rf *.o

fclean: clean
	-rm -rf ../../lib/liblist.a
	-rm -rf ../../bin/main

re: fclean all

test: all ../../bin/main
	-../../bin/main
	make fclean

valgrind: all ../../bin/main
	-valgrind ../../bin/main
	make fclean

.SILENT:
