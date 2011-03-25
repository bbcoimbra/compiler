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
typedef enum {op_k, id_k, const_k} exp_kind;
typedef enum {Void, Integer, Boolean} exp_type;

typedef struct tree_node_t {
	struct tree_node_t *child[MAX_CHILDREN];
	struct tree_node_t *next;
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
} tree_node;

#endif /* _GLOBAL_H_ */

