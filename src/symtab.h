#ifndef _SYMTAB_H
#define _SYMTAB_H

#define HASH_TABLE_SIZE 1117
#define VAR_LOCATIONS 512

struct locations {
	int locations[VAR_LOCATIONS + 1];
};

struct symtab_t {
	char * id;
	struct locations l;
	struct symtab_t * next;
};


unsigned int hash (char * id);
struct symtab_t ** symtab_new(void);
int symtab_insert (struct symtab_t ** tab, char * id);
struct symtab_t * symtab_lookup (struct symtab_t ** tab, char * id);
int symtab_destroy(struct symtab_t ** tab);
void symtab_print(struct symtab_t ** tab);


#endif /* _SYMTAB_H */


