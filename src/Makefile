CC=gcc
CFLAGS=-Wall -O0 -ggdb -std=c99
OBJECTS= util.o parser.o scanner.o
COMPILER_O= compiler.o

all:	scanner_tester

yacc:
	yacc -d parser.y

lex: yacc
	flex scanner.l

.c: lex
	$(CC) $(CFLAGS) -o $@ $@.c

scanner_tester: lex $(OBJECTS)
	$(CC) $(CFLAGS) -c -o scanner_tester.o scanner_tester.c
	$(CC) -o $@ $(OBJECTS) scanner_tester.o

compiler: lex $(OBJECTS)
	$(CC) $(CFLAGS) -c -o compiler.o compiler.c
	$(CC) -o $@ $(OBJECTS) $(COMPILER_O)

clean:
	rm -f *.o scanner.[ch] parser.[ch]

distclean: clean
	rm compiler