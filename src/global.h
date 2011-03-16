#ifndef _GLOBAL_H_

#define _GLOBAL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 3

typedef enum {stmt_k, exp_k} node_kind;
typedef enum {if_k, while_k, assign_k, write_k, read_k} stmt_kind;
typedef enum {op_k, id_k} exp_kind;

typedef struct tree_node {
	struct tree_node *child[MAX_CHILDREN];
	struct tree_node *next;
	int lineno;
	node_kind nodek;
	union {
		stmt_kind stmt;
		exp_kind exp;
	} kind;
	union {
		token_type op;
		int val;
		char *name;
	} attr;
	exp_type type;
} TreeNode;

#endif /* _GLOBAL_H_ */
