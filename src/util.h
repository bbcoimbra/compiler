#ifndef _UTIL_H_
#define _UTIL_H_

struct token_t * new_token (void);

struct node_t * new_expr_node (enum expr_kind kind);
struct node_t * new_stmt_node (enum stmt_kind kind);
void print_node (struct node_t * node);
void print_tree (struct node_t * n);

char *copy_str(char * str);

#endif  /* _UTIL_H_ */
