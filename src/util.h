#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>
#include "global.h"

tree_node * new_token(void);
tree_node * new_expr_node(int kind);
tree_node * new_stmt_node(int kind);
void print_node(tree_node * n);

#endif  /* _UTIL_H_ */
