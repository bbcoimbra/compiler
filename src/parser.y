%{
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "util.h"
#include "scanner.h"
int yyerror(char *s);
%}


%union {
	tree_node * node;
}

%defines "parser.h"
%output "parser.c"

%token AND ATTR ELSE END EQ GE GT IF LE LPAREN LT ;
%token MINUS NEQ OR OVER PLUS READ RPAREN SEMI TIMES ;
%token WHILE WRITE ERROR ;
%token <node> NUM;
%token <node> ID;

%type <node> stmts stmt if_decl while_decl attrib_decl read_decl write_decl;
%type <node>  bool join equality rel term;
%type <node> expr factor;

%left EQ NEQ;
%left GE GT LE LT;
%left TIMES OVER;
%left PLUS MINUS;
%left LPAREN;
%nonassoc ATTR;

%start stmts;

%%

stmts	: stmts SEMI stmt SEMI
				{
					tree_node * node =  $1;
					if(node != NULL)
					{
						while(node->next != NULL)
							node = node->next;
						node->next = $3;
						$$ = $1;
					}
					else $$ = $1;
				}
			| stmt SEMI	{ $$ = $1;}
			;

stmt		: if_decl	{$$ = $1;}
			  | while_decl	{$$ = $1;}
				| attrib_decl	{$$ = $1;}
				| read_decl	{$$ = $1;}
				| write_decl	{$$ = $1;}
				;

if_decl		: IF LPAREN bool RPAREN stmts END
							{ $$ = new_stmt_node(if_k);
								$$->child[0] = $3;
								$$->child[1] = $5;
							}
					| IF LPAREN bool RPAREN stmts ELSE stmts END
							{ $$ = new_stmt_node(if_k);
								$$->child[0] = $3;
								$$->child[1] = $5;
								$$->child[2] = $7;
							}
					;

while_decl	: WHILE LPAREN bool RPAREN stmts END
							{ $$ = new_stmt_node(while_k);
								$$->child[0] = $3;
								$$->child[1] = $5;
							}
						;

attrib_decl	: ID
							{ $<node>$ = new_expr_node(id_k);
								(*$<node>$).attr.name = strdup($1.name);
							}
						ATTR expr
							{ $$ = new_stmt_node(attrib_k);
								$$->child[0] = $4;
							}
						;

read_decl: READ ID
					{ $$ = new_expr_node(id_k);
						$$->attr.name = strdup($2.name);
					}
	  ;

write_decl: WRITE ID
					{ $$ = new_expr_node(id_k);
						$$->attr.name = strdup($2.name);
					}
	   ;

expr: expr PLUS term
      {	$$ = new_expr_node(op_k);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = PLUS;
			}
		| expr MINUS term
			{	$$ = new_expr_node(op_k);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = MINUS;
			}
		| term  {$$ = $1;}
		;

bool	: bool OR join
				{	$$ = new_expr_node(op_k);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = OR;
				}
			| join  {$$ = $1;}
			;

join	: join AND equality
				{ $$ = new_expr_node(op_k);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = AND;
				}
			| equality          {$$ = $1;}
			;

equality	: equality EQ rel
						{	$$ = new_expr_node(op_k);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = EQ;
						}
					| equality NEQ rel
						{	$$ = new_expr_node(op_k);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = NEQ;
						}
					| rel   {$$ = $1;}
					;

rel	: expr GT expr
			{	$$ = new_expr_node(op_k);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = GT;
			}
		| expr LT expr
			{	$$ = new_expr_node(op_k);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = LT;
			}
		| expr GE expr
			{	$$ = new_expr_node(op_k);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = GE;
			}
		| expr LE expr
			{	$$ = new_expr_node(op_k);
				$$->child[0] = $1;
				$$->child[1] = $3;
				$$->attr.op = LE;
			}
		| expr	{$$ = $1;}
		;

term	: term TIMES factor
				{ $$ = new_expr_node(op_k);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = TIMES;
				}
			| term OVER factor
				{	$$ = new_expr_node(op_k);
					$$->child[0] = $1;
					$$->child[1] = $3;
					$$->attr.op = OVER;
				}
			| factor{$$ = $1;}
			;

factor	: LPAREN expr RPAREN {$$ = $2;}
				| ID
					{ $$ = new_expr_node(id_k);
						$$->attr.name = strdup($1.name);
					}
				| NUM	{
							 $$ = new_expr_node(const_k);
				       $$->attr.val = $1.val;
							}
				;
%%

int yyerror(char *s) {
  printf("syntax error: line %d: %s\n", yylineno, s);
	return 0;
}

