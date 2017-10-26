CC = gcc
CFLAGS = -std=c99 -I../../include/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = ../../lib

mainprog_c = minishell.c
out_name = minishell

all: $(mainprog_c) ../../lib/libmy.a
	$(CC) $(CFLAGS) -o $(out_name) $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy

clean:
	-rm ./$(out_name)

fclean: clean

re: fclean all

test: all
	-./$(out_name)
	make fclean

allDB: $(mainprog_c)
	$(CC) $(CFLAGS) -o $(out_name) $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy -g

debug: allDB
	-gdb ./$(out_name)
	make fclean

valgrind: allDB
	-valgrind ./$(out_name)
	make fclean

.SILENT:
