CC = gcc
CFLAGS = -std=c99 -Iinclude/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = lib

mylib_o = src/my/my_alpha.o src/my/my_int.o src/my/my_strcat.o src/my/my_strdup.o src/my/my_strncmp.o src/my/my_strrindex.o src/my/my_atoi.o src/my/my_num_base.o src/my/my_strcmp.o src/my/my_strfind.o src/my/my_strnconcat.o src/my/my_char.o src/my/my_revstr.o src/my/my_strconcat.o src/my/my_strindex.o src/my/my_strncpy.o src/my/my_digits.o src/my/my_str.o src/my/my_strcpy.o src/my/my_strlen.o src/my/my_strrfind.o src/my/my_vect2str.o

mylist_o = src/list/new_node.o src/list/add_node.o src/list/add_elem.o src/list/append.o src/list/add_node_at.o src/list/remove_node.o src/list/remove_last.o src/list/remove_node_at.o src/list/count_s_nodes.o src/list/empty_list.o src/list/node_at.o src/list/elem_at.o src/list/traverse_int.o src/list/traverse_char.o src/list/traverse_string.o src/list/debug_int.o src/list/debug_char.o src/list/debug_string.o src/list/print_int.o src/list/print_char.o src/list/print_string.o

mainprog_c = test/test_list.c

all: lib/libmy.a lib/liblist.a

lib/liblist.a: $(mylist_o)
	ar -rc lib/liblist.a $(mylist_o)
	ranlib lib/liblist.a

lib/libmy.a: $(mylib_o)
	ar -rc lib/libmy.a $(mylib_o)
	ranlib lib/libmy.a

bin/main: lib/libmy.a lib/liblist.a
	$(CC) $(CFLAGS) -o bin/main $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy

clean:
	rm -rf src/my/*.o
	rm -rf src/list/*.o

fclean: clean
	-rm -rf lib/*
	-rm -rf bin/*

re: fclean all

test: all bin/main
	-bin/main
	make fclean

valgrind: all bin/main
	-valgrind bin/main
	make fclean

.SILENT:
