#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "global.h"
#include "util.h"
#include "parser.h"
#include "scanner.h"

extern int errno;
FILE *yyin;

int main(int argc, char **argv, char **env)
{
	union YYSTYPE * t = (union YYSTYPE *)malloc(sizeof(union YYSTYPE));
	int token_type;

	if ((yyin = fopen(argv[1], "r")) == NULL)
	{
		perror("failed to open file\n");
		exit(EXIT_FAILURE);
	}
	while ((token_type = yylex(t)))
		print_token(token_type, t->token);

	return EXIT_SUCCESS;

}