#ifndef _UTIL_H_
#define _UTIL_H_

struct token_t * new_token (void);
struct tree_node_t * new_expr_node (int kind);
struct tree_node_t * new_stmt_node (int kind);
void print_node (struct tree_node_t * n);


#endif  /* _UTIL_H_ */
