#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "util.h"

struct token_t * new_token(void) {
	struct token_t * t = (struct token_t *) malloc(sizeof(struct token_t));
	if (t == NULL) {fprintf(stderr, "fatal: out of memory\n"); exit(EXIT_FAILURE);}
	t->type = 0;
	t->value.num = 0;
	t->value.name = NULL;
	return t;
}

}

struct tree_node_t * new_expr_node(int kind)
{
	struct tree_node_t * n = (struct tree_node_t *) malloc(sizeof(struct tree_node_t));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->node_k = kind;
	n->attr.name = NULL;
	return n;
}

struct tree_node_t * new_stmt_node(int kind)
{
	struct tree_node_t *n = (struct tree_node_t *) malloc(sizeof(struct tree_node_t));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->node_k = kind;
	return n;
}

void print_node(struct tree_node_t * n)
{
	switch(n->node_k)
	{
		case stmt_k:
			printf("Stament\n");
			break;
		case expr_k:
			printf("Expression\n");
			break;
	}
	return;
}
