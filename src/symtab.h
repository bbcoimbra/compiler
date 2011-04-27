#ifndef _SYMTAB_H
#define _SYMTAB_H

#define VAR_LOCATIONS 512

struct symtab_t {
	char * id;
	int locations[VAR_LOCATIONS + 1];
	struct symtab_t * next;
};

unsigned int * weigth_array;

unsigned int * generate_weigths (int size);
unsigned int hash (char * id, unsigned int weigths[], int size);
struct symtab_t * symtab_new(int size);
int symtab_insert (struct symtab_t * tab, char * id);
int symtab_check (struct symtab_t * tab, char * id);
int symtab_remove (struct symtab_t * tab, char * id);
int symtab_destroy(struct symtab_t * tab);


#endif /* _SYMTAB_H */


