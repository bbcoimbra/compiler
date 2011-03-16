CC=gcc
CFLAGS=-Wall -O0 -ggdb
OBJECTS= parser.o scanner.o compiler.o

all: compiler

yacc:
	bison -d parser.y

lex: yacc
	flex scanner.l

.c: lex
	$(CC) $(CFLAGS) -o $@ $@.c

compiler: lex $(OBJECTS)
	$(CC) -c -o $@ *.o

clean:
	rm -f *.o scanner.[ch] parser.tab.?

distclean: clean
	rm compiler