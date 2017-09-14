COMPILER = gcc
COMPILERFLAGS = -std=c99 -Iinclude/ -Ilib/ -Isrc/my/ -Wall -Werror --pedantic
MAINPROG = test/test_mylib.c
MAINDEPENDS = include/my.h
MAINOUT = bin/test

build: $(MAINPROG) $(MAINDEPENDS)
	@$(COMPILER) $(COMPILERFLAGS) $(MAINPROG) -o $(MAINOUT)

buildLib: $(MAINDEPENDS)
	@$(COMPILER) -c $(COMPILERFLAGS) src/my/*.c
	@ar -rc lib/libmy.a *.o
	@rm -f *.o

try: $(MAINPROG) $(MAINDEPENDS)
	@$(COMPILER) $(COMPILERFLAGS) $(MAINPROG) -o testing.out
	@./testing.out
	@rm -f testing.out

debug: $(MAINPROG) $(MAINDEPENDS)
	@$(COMPILER) $(COMPILERFLAGS) $(MAINPROG) -o debug.out -g
	@gdb ./debug.out
	@rm -f debug.out

valgrind: $(MAINPROG) $(MAINDEPENDS)
	@$(COMPILER) $(COMPILERFLAGS) $(MAINPROG) -o debug.out -g
	@valgrind ./debug.out
	@rm -f debug.out
