#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "util.h"
#include "compiler-parser.h"
#include "symtab.h"
#include "cgen.h"

FILE *yyin;
extern struct symtab_t ** stab;

void usage (char * arg);

int main(int argc, char **argv, char **env)
{

	FILE *cfile, *dotfile;
	int print_st = 0, print_ast = 0;
	int opt;

	while ((opt = getopt(argc, argv, "std:c:")) != -1)
	{
		switch(opt)
		{
			case 's':
				print_st = 1;
				break;
			case 't':
				print_ast = 1;
				break;
			case 'd':
				dotfile = fopen(optarg, "w");
				break;
			case 'c':
				cfile = fopen(optarg, "w");
				break;
			default:
				usage(argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if (optind >= argc)
	{
		fprintf (stderr, "Error: missed  input file.\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	yyin = fopen(argv[optind], "r");
	stab = symtab_new();
	if (yyparse() != 0)
	{
		fprintf(stderr, "Compilation failure!\n");
		exit(EXIT_FAILURE);
	}
	if (print_ast)
		print_tree(ast);
	if (print_st)
		symtab_print(stab);
	if(cfile)
		cgen(cfile, ast, stab);

	return EXIT_SUCCESS;

}

void usage (char * arg)
{
	fprintf(stderr, "Usage: %s [-s] [-t] [-d <DOT_file_name>] [-c <C_file_name>] <input_file>\n", arg);
	return;
}

