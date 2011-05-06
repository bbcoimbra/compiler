#include <stdlib.h>
#include "global.h"
#include "dotgen.h"

void generate_dot (FILE * file, struct node_t * ast)
{
	emit_preamble(file);
	gen_graph (file, ast);
	gen_shapes (file, ast);
	emit_finally (file);
}

void emit_preamble (FILE * file)
{
	fprintf (file, "digraph program {\n");
	return;
}

void emit_finally (FILE * file)
{
	fprintf (file, "}\n");
	return;
}

void gen_graph (FILE * file, struct node_t * node)
{
	if (node && node->kind == stmt_k)
	{
		switch (node->type.stmt)
		{
			case if_k:
				break;
			case while_k:
				break;
			case read_k:
				break;
			case write_k:
				break;
			case attrib_k:
				break;
			default:
				fprintf(stderr, "BUG\n");
				exit(EXIT_FAILURE);
		}
	}
	return;
}

void gen_shapes (FILE * file, struct node_t * node)
{
	return;
}
