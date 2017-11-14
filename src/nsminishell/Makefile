CC = gcc
CFLAGS = -I../../include/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = ../../lib

mainprog_c = nsminishell.c
out_name = nsminishell

all: $(mainprog_c) ../../lib/libmy.a ../../lib/liblist.a
	$(CC) $(CFLAGS) -o $(out_name) $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy -lncurses -ltinfo

clean:
	-rm ./$(out_name)

fclean: clean

re: fclean all

test: all
	-./$(out_name)
	make fclean

allDB: $(mainprog_c)
	$(CC) $(CFLAGS) -o debug $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lcurses -ltinfo -g

debug: allDB
	-gdb ./debug
	make fclean

valgrind: allDB
	-valgrind ./debug
	make fclean

.SILENT:
