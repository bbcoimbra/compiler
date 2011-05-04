#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "compiler-parser.h"
#include "symtab.h"
#include "cgen.h"

void declare_variables (FILE * cfile, struct symtab_t ** stab);
void gen_c (FILE * cfile, struct node_t * ast);
void emit_op (FILE * cfile, struct node_t * node);
void emit_const (FILE * cfile, struct node_t * node);
void emit_id (FILE * cfile, struct node_t * node);
void emit_if (FILE * cfile, struct node_t * node);
void emit_while (FILE * cfile, struct node_t * node);
void emit_attrib (FILE * cfile, struct node_t * node);
void emit_read (FILE * cfile, struct node_t * node);
void emit_write (FILE * cfile, struct node_t * node);

void generate_c (FILE * cfile, struct node_t * ast, struct symtab_t ** stab)
{
	fprintf(cfile, "#include <unistd.h>\n");
	fprintf(cfile, "#include <stdlib.h>\n");
	fprintf(cfile, "#include <stdio.h>\n");
	fprintf(cfile, "int main (int argc, char **argv)\n");
	fprintf(cfile, "{\n");
	declare_variables(cfile, stab);
	gen_c(cfile, ast);
	fprintf(cfile, "exit(EXIT_SUCCESS)\n");
	fprintf(cfile, "}\n");
	return;
}

void declare_variables (FILE * cfile, struct symtab_t ** stab)
{
	int i;
	struct symtab_t * entry;

	fprintf(cfile, "  int");
	for (i = 0; i < HASH_TABLE_SIZE ; i++)
	{
		static int first = 1;
		entry = *(stab + i);
		if (entry != NULL && entry->id != NULL)
			if (first)
			{
				fprintf(cfile, " %s", entry->id);
				first = 0;
			}
			else
				fprintf(cfile, ", %s", entry->id);
	}
	fprintf(cfile, ";\n");
	return;
}

void gen_c (FILE * cfile, struct node_t * ast)
{
	struct node_t * node;
	node = ast;
	if (node != NULL)
	{
		switch (node->kind)
		{
			case stmt_k:
				switch (node->type.stmt)
				{
					case if_k:
						emit_if (cfile, node);
						break;
					case while_k:
						emit_while (cfile, node);
						break;
					case attrib_k:
						emit_attrib (cfile, node);
						break;
					case read_k:
						emit_read (cfile, node);
						break;
					case write_k:
						emit_write (cfile, node);
						break;
				}
				break;
			case expr_k:
				switch (node->type.expr)
				{
					case op_k:
						emit_op (cfile, node);
						break;
					case id_k:
						emit_id (cfile, node);
						break;
					case const_k:
						emit_const (cfile, node);
						break;
				}
				break;
			default:
				fprintf (stderr, "This shouldn't happended. You probabily found BUG.");
				exit (EXIT_FAILURE);
		}
		gen_c(cfile, node->next);
	}
}

void emit_op (FILE * cfile, struct node_t * node)
{
	gen_c (cfile, node->child[0]);
	switch (node->attr.op)
	{
		case AND:
			fprintf (cfile, " && ");
			break;
		case OR:
			fprintf (cfile, " || ");
			break;
		case EQ:
			fprintf (cfile, " == ");
			break;
		case NEQ:
			fprintf (cfile, " != ");
			break;
		case GE:
			fprintf (cfile, " >= ");
			break;
		case GT:
			fprintf (cfile, " > ");
			break;
		case LE:
			fprintf (cfile, " <= ");
			break;
		case LT:
			fprintf (cfile, " < ");
			break;
		case PLUS:
			fprintf (cfile, " + ");
			break;
		case MINUS:
			fprintf (cfile, " - ");
			break;
		case TIMES:
			fprintf (cfile, " * ");
			break;
		case OVER:
			fprintf (cfile, " / ");
			break;
	}
	gen_c (cfile, node->child[1]);
	return;
}
void emit_id (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "%s", node->attr.name);
	return;
}

void emit_const (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "%d", node->attr.val);
	return;
}

void emit_if (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "if (");
	gen_c (cfile, node->child[0]);
	fprintf (cfile, ")\n{\n");
	gen_c (cfile, node->child[1]);
	fprintf (cfile, "}\n");
	if (node->child[2])
	{
		fprintf (cfile, "else\n");
		fprintf (cfile, "{\n");
		gen_c (cfile, node->child[2]);
		fprintf (cfile, "}\n");
	}
	return;
}

void emit_while (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "while (");
	gen_c (cfile, node->child[0]);
	fprintf (cfile, ")\n{\n");
	gen_c (cfile, node->child[1]);
	fprintf (cfile, "}\n");
	return;
}

void emit_attrib (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "%s = ", node->attr.name);
	gen_c (cfile, node->child[0]);
	fprintf (cfile, ";\n");
}

void emit_read (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "scanf(\"%%d\", &");
	gen_c (cfile, node->child[0]);
	fprintf (cfile, ");\n");
	return;
}

void emit_write (FILE * cfile, struct node_t * node)
{
	fprintf (cfile, "printf(\"%%d\", ");
	gen_c (cfile, node->child[0]);
	fprintf (cfile, ");\n");
	return;
}

