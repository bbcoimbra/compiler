#ifndef _DOTGEN_H_
#define _DOTGEN_H_

#include <stdio.h>
#include "global.h"

void dot_emit_preamble (FILE * file);
void dot_gen_graph (FILE * file, struct node_t * node, struct node_t * context);
void dot_gen_shapes (FILE * file, struct node_t * node);
void dot_emit_finally (FILE * file);

void dot_emit_if (FILE * file, struct node_t * node, struct node_t * context);
void dot_emit_while (FILE * file, struct node_t * node, struct node_t * context);

#endif /* _DOTGEN_H_ */
