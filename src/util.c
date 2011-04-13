#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "util.h"
#include "parser.h"

struct token_t * new_token(void) {
	struct token_t * t = (struct token_t *) malloc(sizeof(struct token_t));
	if (t == NULL) {fprintf(stderr, "fatal: out of memory\n"); exit(EXIT_FAILURE);}
	t->type = 0;
	t->value.num = 0;
	t->value.name = NULL;
	return t;
}

void print_token (int type, struct token_t * t){
	printf("Token: %d", type);
	switch (type)
	{
		case AND:
			printf ("(AND)");
			break;
		case ATTR:
			printf ("(ATTR)");
			break;
		case ELSE:
			printf ("(ELSE)");
			break;
		case END:
			printf ("(END)");
			break;
		case EQ:
			printf ("(EQ)");
			break;
		case GE:
			printf ("(GE)");
			break;
		case GT:
			printf ("(GT)");
			break;
		case IF:
			printf ("(IF)");
			break;
		case LE:
			printf ("(LE)");
			break;
		case LPAREN:
			printf ("(LPAREN)");
			break;
		case LT:
			printf ("(LT)");
			break;
		case MINUS:
			printf ("(MINUS)");
			break;
		case NEQ:
			printf ("(NEQ)");
			break;
		case OR:
			printf ("(OR)");
			break;
		case OVER:
			printf ("(OVER)");
			break;
		case PLUS:
			printf ("(PLUS)");
			break;
		case READ:
			printf ("(READ)");
			break;
		case RPAREN:
			printf ("(RPAREN)");
			break;
		case SEMI:
			printf ("(SEMI)");
			break;
		case TIMES:
			printf ("(TIMES)");
			break;
		case WHILE:
			printf ("(WHILE)");
			break;
		case WRITE:
			printf ("(WRITE)");
			break;
		case ID:
			printf (" (ID), Name: %s", t->value.name);
			break;
		case NUM:
			printf (" (NUM), Value: %d", t->value.num);
			break;
	}
	printf("\n");
	return;
}

struct node_t * new_expr_node(enum expr_kind kind)
{
	struct node_t * n = (struct node_t *) malloc (sizeof (struct node_t));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->kind = kind;
	n->attr.name = NULL;
	return n;
}

struct node_t * new_stmt_node(enum stmt_kind kind)
{
	struct node_t *n = (struct node_t *) malloc(sizeof(struct node_t));
	int i;

	for(i=0 ; i<3; i++)
		n->child[i] = NULL;
	n->next = NULL;
	n->lineno = 0;
	n->kind = kind;
	return n;
}

void print_node(struct node_t * node)
{
	switch(node->kind)
	{
		case stmt_k:
			printf("Stament\n");
			break;
		case expr_k:
			printf("Expression\n");
			break;
	}
	return;
}

char * copy_str (char * str)
{
	char * aux;
	int len = 0;
	len = strlen(str) + 1;
	aux = (char *) malloc (len);
	memset(aux, 0, len);
	memcpy(aux, str, len - 1);
	return aux;
}

void print_tree (struct node_t * n)
{
	if (n != NULL)
	{
		print_node(n);
		if (n->next != NULL)
			print_tree(n->next);
	}
	return;
}

