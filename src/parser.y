%{
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "scanner.h"
#include "util.h"
%}

%token AND ATTR ELSE END EQ GE GT ID IF LE LPAREN LT ;
%token MINUS NEQ NUM OR OVER PLUS READ RPAREN SEMI TIMES ;
%token WHILE WRITE ERROR ;

%left EQ NEQ;
%left GE GT LE LT;
%left TIMES OVER;
%left PLUS MINUS;
%left LPAREN;
%nonassoc ATTR;

%start prg;

%%

prg	: stmts		{ast = $1;}
    ;

stmts	: stmts SEMI stmt
				{
					YYSTYPE n =  $1;
					if(n != NULL)
					{
						while(n->next != NULL)
							n = n->next;
						n->next = $3;
						$$ = $1;
					}
					else $$ = $3;
				}
			| stmt	{ $$ = $1;}
			;

stmt		: if_decl		{$$ = $1;}
			  | while_decl		{$$ = $1;}
				| attrib_decl SEMI	{$$ = $1;}
				| read_decl SEMI	{$$ = $1;}
				| write_decl SEMI	{$$ = $1;}
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

attrib_decl	: ID ATTR expr
							{ $$ = new_stmt_node(attrib_k);
								$$->child[0] = $3;
							}
						;

read_decl: READ ID
	  ;

write_decl: WRITE ID
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

factor	: LPAREN expr RPAREN {$$ = $1;}
				| ID
					{ $$ = new_expr_node(id_k);
						$$->attr.name = strdup(yytext);
						$$->lineno = yylineno;
					}
				| NUM	{$$ = (int) $1;}
				;
%%

int yyerror(char *s) {
  printf("syntax error: line %d: %s\n", yylineno, s);
	yyerrflag = 1;
	return 0;
}

