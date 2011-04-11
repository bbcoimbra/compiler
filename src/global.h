#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define MAX_CHILDREN 3

typedef enum {stmt_k, expr_k} node_k;
typedef enum {if_k, while_k, attrib_k, write_k, read_k} stmt_kind;
typedef enum {op_k, id_k, const_k} expr_kind;
typedef enum {Void, Integer, Boolean} expr_t;

struct token_t {
  int type;
  union {
    int num;
    char *name;
  } value;
};

struct tree_node_t {
  struct tree_node_t *child[MAX_CHILDREN];
  struct tree_node_t *next;
  int lineno;
  node_k node_kind;
  union {
    stmt_kind stmt;
    expr_kind exp;
  } kind;
  union {
    int op;
    int val;
    char *name;
  } attr;
  expr_t exp_type;
};

#endif /* _GLOBAL_H_ */

