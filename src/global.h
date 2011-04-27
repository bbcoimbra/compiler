#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define MAX_CHILDREN 3

enum node_kind {stmt_k, expr_k};
enum stmt_kind {if_k, while_k, attrib_k, write_k, read_k};
enum expr_kind {op_k, id_k, const_k};

struct token_t {
	int lineno;
  union {
    int val;
    char *name;
  } value;
};

struct node_t {
  struct node_t *child[MAX_CHILDREN];
  struct node_t *next;
  int lineno;
  enum node_kind kind;
  union {
    enum stmt_kind stmt;
    enum expr_kind expr;
  } type;
  union {
    int op;
    int val;
    char *name;
  } attr;
};

struct node_t * ast;

#endif /* _GLOBAL_H_ */

