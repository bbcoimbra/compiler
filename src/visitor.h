#ifndef _VISITOR_H
#define _VISITOR_H

void pre_order(void *fn, struct node_t * node);
void pos_order(void *fn, struct node_t * node);

#endif /* _VISITOR_H */

