CC=gcc
CFLAGS=-Wall -O0 -ggdb
OBJECTS= util.o parser.o scanner.o compiler.o

all: compiler

yacc:
	yacc -d parser.y

lex: yacc
	flex scanner.l

.c: lex
	$(CC) $(CFLAGS) -o $@ $@.c

compiler: lex $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

clean:
	rm -f *.o scanner.[ch] y.tab.?

distclean: clean
	rm compiler