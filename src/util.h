#ifndef _UTIL_H_
#define _UTIL_H_

struct token_t * new_token (void);
void print_token (int type, struct token_t * t);

struct tree_node_t * new_expr_node (int kind);
struct tree_node_t * new_stmt_node (int kind);
void print_node (struct tree_node_t * n);

char *copy_str(char * str);

#endif  /* _UTIL_H_ */
