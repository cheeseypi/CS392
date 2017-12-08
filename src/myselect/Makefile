CC = gcc
CFLAGS = -I../../include/ -Wall -Werror --pedantic
LD_LIBRARY_PATH = ../../lib

mainprog_c = myselect.c
out_name = myselect

all: $(mainprog_c) ../../lib/liblist.a
	$(CC) $(CFLAGS) -o $(out_name) $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lncurses -ltinfo

clean:
	-rm ./$(out_name)

fclean: clean

re: fclean all

test: all
	-./$(out_name) whatev/*
	make fclean

allDB: $(mainprog_c)
	$(CC) $(CFLAGS) -o debug $(mainprog_c) -L$(LD_LIBRARY_PATH) -llist -lncurses -ltinfo -g

debug: allDB
	-gdb --args ./debug *.c
	-rm ./debug

valgrind: allDB
	-valgrind ./debug *.c
	-rm ./debug

.SILENT:
