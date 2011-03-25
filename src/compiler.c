#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"
#include "scanner.h"
#include "y.tab.h"

extern FILE *yyin;

int main(int argc, char **argv, char **env)
{
	FILE *in;
	tree_node *ast, *n;

	yyin = fopen(argv[1], "r");
	ast = yyparse();
	n = ast;
	while(n = yylex())
	{
		print_node(n);
		n = n->next;
	}

	return EXIT_SUCCESS;

}