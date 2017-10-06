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
	-./pipes
	make fclean

valgrind: all
	-valgrind ./pipes
	make fclean

.SILENT:
