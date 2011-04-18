#include <stdlib.h>
#include "global.h"
#include "visitor.h"

void pre_order (void *fn, struct node_t * node)
{
	int i = 0;
	void (*fp) (struct node_t *);
	fp = fn;

	if (node != NULL)
	{
		(*fp)(node);
		for (i = 0 ; i < MAX_CHILDREN ; i++)
			if (node->child[i])
				pre_order(fn, node->child[i]);
		if (node->next != NULL)
			pre_order(fn, node->next);
	}
	return;
}

void pos_order (void *fn, struct node_t * node)
{
	int i = 0;
	void (*fp) (struct node_t *);

	fp = fn;
	if (node != NULL)
	{
		for (i = 0 ; i < MAX_CHILDREN ; i++)
			if (node->child[i])
				pos_order(fn, node->child[i]);
		(*fp)(node);
		if (node->next != NULL)
			pos_order(fn, node->next);
	}
	return;
}
