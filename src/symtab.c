#include "symtab.h"
#include <stdlib.h>
#include <string.h>

#define MAX_HASH_TABLE_ELEMENTS 1031

unsigned int * generate_weigths(int size)
{
	int i;
	weigth_array = (unsigned int *) malloc (sizeof (unsigned int) * size);
	for (i =0 ; i < size ; i++ )
		weigth_array[i] = rand();
	return weigth_array;
}

unsigned int hash(char * id, unsigned int weigths[], int size)
{
	int len, i, j=0;
	unsigned int h, temp=0;

	len = strlen(id);
	for (i = 0; i < len; i++)
	{
		if (j > (size - 1)) j = 0;
		temp = temp + id[i] * weigths[j];
		j++;
	}
	h = temp % MAX_HASH_TABLE_ELEMENTS;
	return h;
}

struct symtab_t * symtab_new(int size)
{
	struct symtab_t * tab;
	tab = (struct symtab_t *) malloc (sizeof (struct symtab_t) * (size + 1));
	return tab;
}

int symtab_insert (struct symtab_t * tab, char * id)
{
	return 0;
}

int symtab_check (struct symtab_t * tab, char * id)
{
	return 0;
}

int symtab_remove (struct symtab_t * tab, char * id)
{
	return 0;
}

int symtab_destroy (struct symtab_t * tab)
{
	return 0;
}

