#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "dotgen.h"
#include "compiler-parser.h"

char * gen_name(struct node_t *node);
void dot_emit_preamble (FILE * file);
void dot_gen_labels (FILE * file, struct node_t * node);
void dot_gen_graph (FILE * file, struct node_t * node, struct node_t * context);
void dot_gen_shapes (FILE * file,	struct node_t * node);
void dot_emit_finally (FILE * file);
void dot_emit_if (FILE * file, struct node_t * node,	struct node_t * context);
void dot_emit_while (FILE * file, struct node_t * node,	struct node_t * context);

void generate_dot (FILE * file, struct node_t * ast)
{
	dot_emit_preamble(file);
	dot_gen_labels (file, ast);
	dot_gen_graph (file, ast, NULL);
	dot_gen_shapes (file, ast);
	dot_emit_finally (file);
}

void dot_emit_preamble (FILE * file)
{
	fprintf (file, "digraph program {\n");
	fprintf (file, "node [shape=box];\n");
	return;
}

void dot_emit_finally (FILE * file)
{
	fprintf (file, "}\n");
	return;
}

void dot_print_op(FILE * file, int kind)
{
	switch (kind)
	{
		case PLUS:
			fprintf(file, " + ");
			break;
		case MINUS:
			fprintf (file, " - ");
			break;
		case TIMES:
			fprintf (file, " * ");
			break;
		case OVER:
			fprintf (file, " / ");
			break;
		case EQ:
			fprintf (file, " == ");
			break;
		case NEQ:
			fprintf (file, " != ");
			break;
		case AND:
			fprintf (file, " && ");
			break;
		case OR:
			fprintf (file, " || ");
			break;
		case GE:
			fprintf (file, " >= ");
			break;
		case GT:
			fprintf (file, " > ");
			break;
		case LE:
			fprintf (file, " <= ");
			break;
		case LT:
			fprintf (file, " < ");
			break;
		default:
			fprintf(file, "   ");
			break;
	}
	return;
}
void dot_gen_if_label(FILE * file, struct node_t * node)
{
	char * name;
	if (node && node->kind == stmt_k && node->type.stmt == if_k)
	{
		name = gen_name (node);
		fprintf (file, "%s [label = \" ", name);
		dot_gen_labels (file, node->child[0]);
		fprintf (file, "\" ];\n");
		free (name);

		dot_gen_labels (file, node->child[1]);
		dot_gen_labels (file, node->child[2]);
	}
	return;
}

void dot_gen_while_label(FILE * file, struct node_t * node)
{
	char * name;
	if (node && node->kind == stmt_k && node->type.stmt == while_k)
	{
		name = gen_name (node);
		fprintf (file, "%s [label = \" ", name);
		dot_gen_labels (file, node->child[0]);
		fprintf (file, "\" ];\n");
		free (name);

		dot_gen_labels (file, node->child[1]);
	}
	return;
}

void dot_gen_labels (FILE * file, struct node_t * node)
{
	char *name;

	if (node)
	{
		switch (node->kind)
		{
			case stmt_k:
				switch (node->type.stmt)
				{
					case if_k:
						dot_gen_if_label(file, node);
						break;
					case while_k:
						dot_gen_while_label(file, node);
						break;
					case attrib_k:
						name = gen_name (node);
						fprintf (file, "%s [label = \"", name);
						fprintf (file, "%s = ", node->attr.name);
						dot_gen_labels (file, node->child[0]);
						fprintf (file, "\" ];\n");
						free (name);
						break;
					case read_k:
						name = gen_name (node);
						fprintf (file, "%s [label = \"", name);
						fprintf(file, "leia ");
						dot_gen_labels (file, node->child[0]);
						fprintf (file, "\" ];\n");
						free (name);
						break;
					case write_k:
						name = gen_name (node);
						fprintf (file, "%s [label = \"", name);
						fprintf(file, "escreva ");
						dot_gen_labels (file, node->child[0]);
						fprintf (file, "\" ];\n");
						free (name);
						break;
				}
				break;
			case expr_k:
				switch (node->type.expr) {
					case const_k:
						fprintf (file, "%d", node->attr.val);
						break;
					case op_k:
						dot_gen_labels (file, node->child[0]);
						dot_print_op(file, node->attr.op);
						dot_gen_labels (file, node->child[1]);
						break;
					case id_k:
						fprintf (file, "%s", node->attr.name);
						break;
				}
				break;
		}
		dot_gen_labels (file, node->next);
	}
}

void dot_gen_graph (FILE * file, struct node_t * node, struct node_t * context)
{
	char * name, * next;
	if (node && node->kind == stmt_k)
	{
		switch (node->type.stmt)
		{
			case if_k:
				dot_emit_if (file, node, context);
				break;
			case while_k:
				dot_emit_while (file, node, context);
				break;
			case read_k:
			case write_k:
			case attrib_k:
				name = gen_name (node);
				fprintf (file, "%s", name);
				if (node->next != NULL)
				{
					next = gen_name (node->next);
					fprintf (file, " -> %s", next);
					free (next);
				}
				else
				{
					if (context != NULL)
					{
						next = gen_name (context);
						fprintf (file, " -> %s", next);
						free (next);
					}
				}
				fprintf(file, ";\n");
				free (name);
				dot_gen_graph (file, node->next, context);
				break;
			default:
				fprintf(stderr, "BUG\n");
				exit(EXIT_FAILURE);
		}
	}
	return;
}

void dot_gen_shapes (FILE * file, struct node_t * node)
{
	if (node && node->kind == stmt_k)
	{
		char * name;
		int i = 0;
		name = gen_name (node);
		switch (node->type.stmt)
		{
			case if_k:
				fprintf (file, "%s [shape=diamond];", name);
				break;
			case while_k:
				fprintf (file, "%s [shape=diamond];", name);
				break;
			case read_k:
			case write_k:
			case attrib_k:
				/* do nothing */
				break;
			default:
				fprintf(stderr, "BUG\n");
				exit(EXIT_FAILURE);
		}
		free(name);
		for (i = 0; i < MAX_CHILDREN; i++)
			dot_gen_shapes (file, node->child[i]);
		dot_gen_shapes (file, node->next);
	}
	return;
}

void dot_emit_if (FILE * file, struct node_t * node, struct node_t * context)
{
	char *node_name, *child_name;

	node_name = gen_name (node);
	child_name = gen_name (node->child[1]);
	fprintf(file, "%s -> %s [label =\"true\"];\n", node_name, child_name);
	dot_gen_graph (file, node->child[1], (node->next != NULL ? node->next : context));
	if (node->child[2] != NULL)
	{
		free (child_name);
		child_name = gen_name (node->child[2]);
		fprintf(file, "%s -> %s [label =\"false\"];\n", node_name, child_name);
		dot_gen_graph (file, node->child[2], (node->next != NULL ? node->next : context));
	}
	else
	{
		char * next;
		if (node->next != NULL) next = gen_name (node->next);
		else next = gen_name (context);
		fprintf (file, "%s -> %s [label =\"false\"];\n", node_name, next);
		free (next);
	}
	free (node_name); free (child_name);
	dot_gen_graph (file, node->next, context);
	return;
}

void dot_emit_while (FILE * file, struct node_t * node, struct node_t * context)
{
	char *node_name, *child_name;
	char * next;

	node_name = gen_name (node);
	child_name = gen_name (node->child[1]);
	fprintf(file, "%s -> %s [label =\"true\"];\n", node_name, child_name);
	dot_gen_graph (file, node->child[1], node);
	if (node->next)	next = gen_name (node->next);
	else next = gen_name (context);
	fprintf (file, "%s -> %s [label =\"false\"];\n", node_name, next);
	free (next);
	free (node_name); free (child_name);
	dot_gen_graph (file, node->next, context);
	return;
}

char * gen_name(struct node_t * node)
{
	char * str;
	str = (char *) malloc (sizeof(char) * 33);
	memset (str, 0, 33);
	switch (node->type.stmt)
		{
			case if_k:
				sprintf(str, "if%d", (int) node);
				break;
			case while_k:
				sprintf(str, "while%d", (int) node);
				break;
			case read_k:
				sprintf(str, "read%d", (int) node);
				break;
			case write_k:
				sprintf(str, "write%d", (int) node);
				break;
			case attrib_k:
				sprintf(str, "attrib%d", (int) node);
				break;
			default:
				fprintf(stderr, "BUG\n");
				exit(EXIT_FAILURE);
		}
	return str;
}

