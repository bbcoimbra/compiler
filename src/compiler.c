#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "util.h"
#include "compiler-parser.h"

FILE *yyin;

int main(int argc, char **argv, char **env)
{

	yyin = fopen(argv[1], "r");
	if (yyparse() != 0)
	{
		fprintf(stderr, "Compilation failure!\n");
		exit(EXIT_FAILURE);
	}
	print_tree2(ast);

	return EXIT_SUCCESS;

}
