#ifndef _DOTGEN_H_
#define _DOTGEN_H_

void emit_preamble (file);
void gen_graph (FILE * file, struct node_t * node);
void gen_shapes (FILE * file, struct node_t * node);
void emit_finally (FILE * file);

#endif /* _DOTGEN_H_ */
