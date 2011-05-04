#include "symtab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned int weight_array[HASH_TABLE_SIZE + 1];

void generate_weights(void)
{
	int i;
	for (i =0 ; i < HASH_TABLE_SIZE ; i++ )
		weight_array[i] = rand();
	weight_array[HASH_TABLE_SIZE + 1] = 0;
	return;
}

unsigned int hash(char * id)
{
	int len, i, j=0;
	unsigned int h, temp=0;

	len = strlen(id);
	for (i = 0; i < len; i++)
	{
		if (j > (HASH_TABLE_SIZE - 1)) j = 0;
		temp = temp + id[i] * weight_array[j];
		j++;
	}
	h = temp % HASH_TABLE_SIZE;
	return h;
}

struct symtab_t ** symtab_new(void)
{
	int i;
	struct symtab_t ** tab;
	generate_weights();
	tab = (struct symtab_t **) malloc (sizeof (struct symtab_t *) * (HASH_TABLE_SIZE + 1));
	*(tab + HASH_TABLE_SIZE + 1) = NULL;
	for (i = 0; i < HASH_TABLE_SIZE ; i++)
	{
		*(tab + i) = (struct symtab_t *) malloc (sizeof (struct symtab_t));
		(**(tab + i)).id = NULL;
	}
	return tab;
}

int symtab_insert (struct symtab_t ** tab, char * id)
{
	struct symtab_t * entry;
	unsigned int h;
	if (id == NULL)
		return -1;
	if ((entry = symtab_lookup (tab, id)) == NULL)
	{
		h = hash (id);
		if ( (**(tab + h)).id == 0x0)
		{
			(**(tab + h)).id = strdup(id);
		}
		else
		{
			entry = *(tab + h);
			while (entry->next != NULL)
				entry = entry->next;
			entry->next = (struct symtab_t *) malloc (sizeof (struct symtab_t));
			entry->next->id = strdup (id);
		}
		return 1;
	}
	return 0;
}

struct symtab_t * symtab_lookup (struct symtab_t ** tab, char * id)
{
	struct symtab_t * entry;
	unsigned int h;

	if (id == NULL)
		return NULL;
	h = hash(id);
	if (((**(tab+h)).id) && (strcmp ( (**(tab + h)).id, id) == 0))
		return *(tab + h);
	else
	{
		entry = *(tab + h);
		while (entry->next != NULL)
		{
			entry = entry->next;
			if (strcmp (entry->id, id) == 0)
				return entry;
		}
	}
	return NULL;
}

int symtab_destroy (struct symtab_t ** tab)
{
	return 0;
}

void symtab_print(struct symtab_t ** tab)
{
	int i;
	struct symtab_t * entry;

	fprintf(stderr, "\n======== Printing Symtab ========\n");
	for (i = 0; i < HASH_TABLE_SIZE; i++)
	{
		entry = *(tab + i);
		if (entry->id && (strlen(entry->id) != 0))
		{
			fprintf(stderr, "Entry %d:\n", i);
			fprintf(stderr, "IDs: %s", entry->id);
			while (entry->next != NULL)
			{
				entry = entry->next;
				fprintf(stderr, ", %s", entry->id);
			}
			fprintf(stderr, "\n");
		}
	}
	return;
}
