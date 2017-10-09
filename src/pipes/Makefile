CC = gcc
CFLAGS = -std=c99 -I../../include/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = ../../lib

mainprog_c = ./pipes.c

all: pipes.c
	$(CC) $(CFLAGS) -o ./pipes $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy

clean:
	rm -rf ./pipes

fclean: clean

re: fclean all

test: all
	-./pipes Hello, World! This is a test.
	make fclean

allDB: pipes.c
	$(CC) $(CFLAGS) -o ./pipes $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lmy -g

debug: allDB
	-gdb ./pipes
	make fclean

valgrind: allDB
	-valgrind ./pipes
	make fclean

.SILENT:
