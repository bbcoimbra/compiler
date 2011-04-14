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
	if (node == NULL)
		return;
	switch (node->kind)
	{
		case stmt_k:
			printf("Stament: ");
			switch (node->type.expr)
			{
				case if_k:
					printf("IF\n");
					break;
				case write_k:
					printf("WRITE\n");
					break;
				case attrib_k:
					printf("ATTRIB\n");
					break;
			}
			break;
		case expr_k:
			printf("Expression\n");
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

void print_tree (struct node_t * n)
{
	int i = 0;

	if (n != NULL)
	{
		print_node(n);
		for (i = 0 ; i < MAX_CHILDREN ; i++)
			print_tree(n->child[i]);
		if (n->next != NULL)
			print_tree(n->next);
	}
	return;
}

