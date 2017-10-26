CC = gcc
CFLAGS = -std=c99 -I../../include/ -Wall -Werror --pedantic -g
LD_LIBRARY_PATH = ../../lib/
mylib_c = my_alpha.c my_int.c my_strcat.c my_strdup.c my_strncmp.c my_strrindex.c my_atoi.c my_num_base.c my_strcmp.c my_strfind.c my_strnconcat.c my_char.c my_revstr.c my_strconcat.c my_strindex.c my_strncpy.c my_digits.c my_str.c my_strcpy.c my_strlen.c my_strrfind.c
mylib_o = my_alpha.o my_int.o my_strcat.o my_strdup.o my_strncmp.o my_strrindex.o my_atoi.o my_num_base.o my_strcmp.o my_strfind.o my_strnconcat.o my_char.o my_revstr.o my_strconcat.o my_strindex.o my_strncpy.o my_digits.o my_str.o my_strcpy.o my_strlen.o my_strrfind.o my_str2vect.o my_vect2str.o
mainprog_c = ../../test/test_mylib.c

all: ../../bin/main

../../lib/libmy.a: $(mylib_o)
	ar -rc ../../lib/libmy.a $(mylib_o)
	ranlib ../../lib/libmy.a

../../bin/main: ../../lib/libmy.a
	$(CC) $(CFLAGS) -o ../../bin/main $(mainprog_c) -L$(LD_LIBRARY_PATH) -lmy

clean:
	rm -rf *.o

fclean: clean
	rm -rf ../../bin/main
	rm -rf ../../lib/libmy.a

re: fclean all

test: all
	-../../bin/main
	make fclean

valgrind: all
	-valgrind ../../bin/main
	make fclean

.SILENT:
