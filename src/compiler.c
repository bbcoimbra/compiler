#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "global.h"

extern FILE *yyin;

int main(int argc, char **argv, char **env)
{
	FILE *in;

	in = fopen(argv[1], "r");
	yyin = in;

	return EXIT_SUCCESS;

}