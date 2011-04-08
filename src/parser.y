%{
#define YYDEBUG 1
#include <stdlib.h>
#include <stdio.h>
#include "global.h"
#include "util.h"
%}

%union{
struct token_t *token;
struct tree_node_t *node;
}

%defines "parser.h"
%output "parser.c"

%token AND ATTR ELSE END EQ GE GT IF LE LPAREN LT ;
%token MINUS NEQ OR OVER PLUS READ RPAREN SEMI TIMES ;
%token WHILE WRITE ;
%token NUM;
%token ID;

%left EQ NEQ;
%left GE GT LE LT;
%left TIMES OVER;
%left PLUS MINUS;
%left LPAREN;
%nonassoc ATTR;

%start stmts;

%{
#include "scanner.h"
#define YYLEX_PARAM yylval_param
void yyerror(char *s);
int yydebug = 1;
%}

%%

stmts : stmts SEMI stmt SEMI
      | stmt SEMI
      ;

stmt  : if_decl
      | while_decl
      | attrib_decl
      | read_decl
      | write_decl
      ;

if_decl  : IF LPAREN bool RPAREN stmts END
         | IF LPAREN bool RPAREN stmts ELSE stmts END
         ;

while_decl : WHILE LPAREN bool RPAREN stmts END
           ;

attrib_decl : ID ATTR expr
            ;

read_decl : READ ID
          ;

write_decl : WRITE ID
           ;

expr : expr PLUS term
     | expr MINUS term
     | term
     ;

bool : bool OR join
     | join
     ;

join : join AND equality
     | equality
     ;

equality : equality EQ rel
         | equality NEQ rel
         | rel
         ;

rel : expr GT expr
    | expr LT expr
    | expr GE expr
    | expr LE expr
    | expr
    ;

term : term TIMES factor
     | term OVER factor
     | factor
     ;

factor : LPAREN expr RPAREN
       | ID
       | NUM
       ;
%%

void yyerror(char *s) {
  printf("syntax error: %s\n", s);
  return;
}

