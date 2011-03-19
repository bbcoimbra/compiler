#include "util.h"

TreeNode * new_token(void) {
	TreeNode * n = (TreeNode *) malloc(sizeof(TreeNode));
	return n;
}

TreeNode * new_expr_node(int kind)
{
	TreeNode * n = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->node_k = kind;
	return n;
}

TreeNode * new_stmt_node(int kind)
{
	TreeNode *n = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->node_k = kind;
	return n;
}

