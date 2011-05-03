#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "symtab.h"
#include "cgen.h"

void cgen (FILE * cfile, struct node_t * ast, struct symtab_t ** stab)
{
	fprintf(cfile, "teste do arquivo C\n");
	return;
}