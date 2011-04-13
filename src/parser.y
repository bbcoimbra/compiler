%{
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "util.h"

int yylex(void);
void yyerror(struct node_t *, ...);

char * saved_name;
%}

%union{
int val;
char * name;
struct token_t *token;
struct node_t *node;
}

%defines "parser.h"
%output "parser.c"

%token AND ATTR ELSE END EQ GE GT IF LE LPAREN LT ;
%token MINUS NEQ OR OVER PLUS READ RPAREN SEMI TIMES ;
%token WHILE WRITE;
%token <val> NUM;
%token <name> ID;

%type <node> stmts stmt while_decl if_decl attrib_decl write_decl read_decl;
%type <node> bool expr factor;

%left EQ NEQ;
%left GE GT LE LT;
%left TIMES OVER;
%left PLUS MINUS;
%left LPAREN;
%nonassoc ATTR;

%%

program : stmts { ast = $1; }
        ;

stmts : stmts stmt
       {
         struct node_t *t = $1;
         if (t != NULL)
         {
           while (t->next != NULL)
             t = t->next;
           t->next = $2;
           $$ = $1;
         }
         else
          $$ = $2;
       }
      | stmt
        { $$ = $1; }
      ;

stmt  : if_decl SEMI
        { $$ = $1; }
      | while_decl SEMI
        { $$ = $1; }
      | attrib_decl SEMI
        { $$ = $1; }
      | read_decl SEMI
        { $$ = $1; }
      | write_decl SEMI
        { $$ = $1; }
      ;

if_decl  : IF LPAREN bool RPAREN stmts END
           {
             $$ = new_stmt_node(if_k);
             $$->child[0] = $3;
             $$->child[1] = $5;
           }
         | IF LPAREN bool RPAREN stmts ELSE stmts END
           {
             $$ = new_stmt_node(if_k);
             $$->child[0] = $3;
             $$->child[1] = $5;
             $$->child[2] = $7;
           }
         ;

while_decl : WHILE LPAREN bool RPAREN stmts END
           {
             $$ = new_stmt_node(while_k);
             $$->child[0] = $3;
             $$->child[1] = $5;
           }
           ;

attrib_decl : ID
            { saved_name = copy_str (yylval.name); }
            ATTR expr
            {
              $$ = new_stmt_node(attrib_k);
              $$->child[0] = $4;
              $$->attr.name = saved_name;
            }
            ;

read_decl : READ ID
          {
            $$ = new_stmt_node(read_k);
            $$->child[0] = $2;
          }
          ;

write_decl : WRITE ID
           {
            $$ = new_stmt_node(write_k);
            $$->child[0] = $2;
           }
           ;

expr : expr PLUS expr
     {
       $$ = new_expr_node(op_k);
       $$->child[0] = $1;
       $$->child[1] = $3;
       $$->attr.op = PLUS;
     }
     | expr MINUS expr
     {
       $$ = new_expr_node(op_k);
       $$->child[0] = $1;
       $$->child[1] = $3;
       $$->attr.op = MINUS;
     }
     | expr TIMES expr
     {
       $$ = new_expr_node(op_k);
       $$->child[0] = $1;
       $$->child[1] = $3;
       $$->attr.op = TIMES;
     }
     | expr OVER expr
     {
       $$ = new_expr_node(op_k);
       $$->child[0] = $1;
       $$->child[1] = $3;
       $$->attr.op = OVER;
     }
     | factor
       { $$ = $1; }
     | bool
       { $$ = $1; }
     ;

bool : expr OR expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = OR;
       }
     | expr AND expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = AND;
       }
     | expr EQ expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = EQ;
       }
     | expr NEQ expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = NEQ;
       }
     | expr GT expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = GT;
       }
     | expr LT expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = LT;
       }
     | expr GE expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = GE;
       }
     | expr LE expr
       {
          $$ = new_expr_node(op_k);
          $$->child[0] = $1;
          $$->child[1] = $3;
          $$->attr.op  = LE;
       }
     | expr
       { $$ = $1; }
     ;

factor : LPAREN expr RPAREN
       { $$ = $2; }
       | ID
         {
           $$ = new_expr_node(id_k);
           $$->attr.name = copy_str (yylval.name);
         }
       | NUM
         {
           $$ = new_expr_node(const_k);
           $$->attr.val = yylval.val;
         }
       ;
%%

void yyerror(struct node_t *s, ...) {
  printf("syntax error: %s\n", s);
  return;
}

