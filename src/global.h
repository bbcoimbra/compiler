#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILDREN 3
#define YYDEBUG 1

typedef enum {stmt_k, expr_k} node_kind;
typedef enum {if_k, while_k, attrib_k, write_k, read_k} stmt_kind;
typedef enum {op_k, id_k} exp_kind;
typedef enum {Void, Integer, Boolean} exp_type;

typedef struct tree_node {
	struct tree_node *child[MAX_CHILDREN];
	struct tree_node *next;
	int lineno;
	node_kind node_k;
	union {	stmt_kind stmt;
		exp_kind exp;
	} kind;
	union {	int op;
		int val;
		char *name;
	} attr;
	exp_type expr_type;
} TreeNode;

# ifndef YYSTYPE
#  define YYSTYPE TreeNode *
# endif

#endif /* _GLOBAL_H_ */

