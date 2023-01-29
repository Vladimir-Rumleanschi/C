CC = gcc
LINKER = gcc
CFLAGS = -std=c99 -Wall # -Werror -Wpointer-arith -Wfatal-errors
DEBUG = -g
PROG1LIBNAME = prog1
PROG1LIBDIR = ../prog1lib/lib

# disable default suffixes
.SUFFIXES:

# library
prog1lib:
	cd $(PROG1LIBDIR) && make

multiset: multiset.c multiset.h
	$(CC) $(CFLAGS) $(DEBUG) -o multiset multiset.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

soccer: soccer.c map.c map.h
	$(CC) $(CFLAGS) $(DEBUG) -o soccer soccer.c map.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)
	
iterator: iterator.h iterator.c btree.h btree.c tree.h tree.c dyn_list.h dyn_list.c dyn_queue.c dyn_queue.h dyn_stack.h dyn_stack.c
	$(LINKER) $(CFLAGS) $(DEBUG) -o iterator iterator.c btree.c tree.c dyn_queue.c dyn_stack.c dyn_list.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

stopwatch: stopwatch.c 
	$(CC) $(CFLAGS) $(DEBUG) -o stopwatch stopwatch.c -L$(PROG1LIBDIR) -l$(PROG1LIBNAME) -lm -iquote$(PROG1LIBDIR)

# delete intermediary files
.PHONY: clean		# do not treat "clean" as a file name
clean:				# special target to remove files: make clean
	rm -rf *.o *.dSYM
