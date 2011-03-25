#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "util.h"

tree_node * new_token(void) {
	tree_node * n = (tree_node *) malloc(sizeof(tree_node));
	if(n == NULL){fprintf(stderr, "fatal: out of memory\n"); exit(EXIT_FAILURE);}
	return n;
}

tree_node * new_expr_node(int kind)
{
	tree_node * n = (tree_node *) malloc(sizeof(tree_node));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->node_k = kind;
	n->attr.name = NULL;
	return n;
}

tree_node * new_stmt_node(int kind)
{
	tree_node *n = (tree_node *) malloc(sizeof(tree_node));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->node_k = kind;
	return n;
}

void print_node(tree_node * n)
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
