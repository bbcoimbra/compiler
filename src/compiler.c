#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "util.h"
#include "parser.h"

FILE *yyin;

int main(int argc, char **argv, char **env)
{
	struct tree_node_t *ast;

	yyin = fopen(argv[1], "r");
	if (yyparse(ast) != 0)
	{
		fprintf(stderr, "Compilation failure!\n");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;

}
