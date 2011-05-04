#ifndef _CGEN_H
#define _CGEN_H

void generate_c (FILE * cfile, struct node_t * ast, struct symtab_t ** stab);

#endif /* _CGEN_H */
