CC = gcc
CFLAGS = -std=c99 -Iinclude/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = lib/
mylib_c = src/my/my_alpha.c src/my/my_int.c src/my/my_strcat.c src/my/my_strdup.c src/my/my_strncmp.c src/my/my_strrindex.c src/my/my_atoi.c src/my/my_num_base.c src/my/my_strcmp.c src/my/my_strfind.c src/my/my_strnconcat.c src/my/my_char.c src/my/my_revstr.c src/my/my_strconcat.c src/my/my_strindex.c src/my/my_strncpy.c src/my/my_digits.c src/my/my_str.c src/my/my_strcpy.c src/my/my_strlen.c src/my/my_strrfind.c
mylib_o = src/my/my_alpha.o src/my/my_int.o src/my/my_strcat.o src/my/my_strdup.o src/my/my_strncmp.o src/my/my_strrindex.o src/my/my_atoi.o src/my/my_num_base.o src/my/my_strcmp.o src/my/my_strfind.o src/my/my_strnconcat.o src/my/my_char.o src/my/my_revstr.o src/my/my_strconcat.o src/my/my_strindex.o src/my/my_strncpy.o src/my/my_digits.o src/my/my_str.o src/my/my_strcpy.o src/my/my_strlen.o src/my/my_strrfind.o
mylist_c = src/my/new_node.c src/my/add_node.c src/my/add_elem.c src/my/append.c src/my/add_node_at.c src/my/remove_node.c src/my/remove_last.c src/my/remove_node_at src/my/count_s_nodes.c src/my/empty_list.c src/my/node_at.c src/my/elem_at.c src/my/traverse_int.c src/my/traverse_char.c src/my/traverse_string.c src/my/debug_int.c src/my/debug_char.c src/my/debug_string.c src/my/print_int.c src/my/print_char.c src/my/print_string.c
mainprog_c = test/test_mylib.c
mainprog_o = test/test_mylib.o

all: bin/main

lib/libmy.a: $(mylib_o)
	ar -rc lib/libmy.a $(mylib_o)
	ranlib lib/libmy.a

bin/main: lib/libmy.a
	$(CC) $(CFLAGS) -o bin/main $(mainprog_c) -L$(LD_LIBRARY_PATH) -lmy

clean:
	rm -rf src/my/*.o

fclean: clean
	rm -rf bin/*

re: fclean all

test: all
	-bin/main
	make fclean

valgrind: all
	-valgrind bin/main
	make fclean

.SILENT:
