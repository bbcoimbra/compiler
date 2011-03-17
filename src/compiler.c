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
	TreeNode * ast;

	in = fopen(argv[1], "r");
	yyin = in;
	ast = yyparse();

	return EXIT_SUCCESS;

}