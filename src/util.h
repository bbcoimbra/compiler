#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdlib.h>
#include "global.h"

TreeNode * new_token(void);
TreeNode * new_expr_node(int kind);
TreeNode * new_stmt_node(int kind);

#endif  /* _UTIL_H_ */
