#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "parser.h"

FILE *yyin;

int main(int argc, char **argv, char **env)
{
	struct tree_node_t *ast, *n;

	yyin = fopen(argv[1], "r");
	ast = yyparse();

	return EXIT_SUCCESS;

}
