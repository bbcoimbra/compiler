#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.h"

static int indent_level = 0;

struct token_t * new_token(void) {
	struct token_t * t = (struct token_t *) malloc(sizeof(struct token_t));
	if (t == NULL) {fprintf(stderr, "fatal: out of memory\n"); exit(EXIT_FAILURE);}
	t->type = 0;
	t->value.num = 0;
	t->value.name = NULL;
	return t;
}

struct node_t * new_expr_node(enum expr_kind kind)
{
	struct node_t * n = (struct node_t *) malloc (sizeof (struct node_t));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->kind = expr_k;
	n->type.expr = kind;
	n->attr.name = NULL;
	return n;
}

struct node_t * new_stmt_node(enum stmt_kind kind)
{
	struct node_t *n = (struct node_t *) malloc(sizeof(struct node_t));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->kind = stmt_k;
	n->type.stmt = kind;
	return n;
}

void print_node(struct node_t * node)
{
	int i;

	for (i = 0 ; i < indent_level ; i++)
		printf("  ");

	if (node == NULL)
		return;
	switch (node->kind)
	{
		case stmt_k:
			printf("Stament: ");
			switch (node->type.stmt)
			{
				case if_k:
					printf("IF\n"); break;
				case write_k:
					printf("WRITE\n"); break;
				case attrib_k:
					printf("ATTRIB to %s\n", node->attr.name); break;
				case while_k:
					printf("WHILE\n"); break;
				case read_k:
					printf("READ\n"); break;
			}
			break;
		case expr_k:
			printf("Expression: ");
			switch (node->type.expr)
			{
				case id_k:
					printf("ID: %s\n", node->attr.name); break;
				case op_k:
					printf("OP: ");
					switch (node->attr.op)
					{
						case EQ:
							printf("=="); break;
						case NEQ:
							printf("!="); break;
						case GE:
							printf(">="); break;
						case GT:
							printf(">"); break;
						case LE:
							printf("<="); break;
						case LT:
							printf("<"); break;
						case PLUS:
							printf("+"); break;
						case MINUS:
							printf("-"); break;
						case TIMES:
							printf("*"); break;
						case OVER:
							printf("/"); break;
					}
					printf("\n");
					break;
				case const_k:
					printf("NUM: %d\n", node->attr.val); break;
			}
			break;
	}
	return;
}

char * copy_str (char * str)
{
	char * aux;
	int len = 0;
	len = strlen(str) + 1;
	aux = (char *) malloc (len);
	memset(aux, 0, len);
	memcpy(aux, str, len - 1);
	return aux;
}

void print_tree (struct node_t * node)
{
	int i = 0;

	if (node != NULL)
	{
		print_node(node);
		for (i = 0 ; i < MAX_CHILDREN ; i++)
			if (node->child[i])
			{
				indent_level++;
				print_tree(node->child[i]);
				indent_level--;
			}
		if (node->next != NULL)
			print_tree(node->next);
	}
	return;
}

