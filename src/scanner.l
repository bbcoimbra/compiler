%option   8bit
%option   warn nodefault
%option   yylineno
%option   outfile="scanner.c" header-file="scanner.h"

%{
#include <string.h>
#include "global.h"
#include "y.tab.h"
TreeNode * new_token(void); 
%}

ws  [[:blank:]\n]*
identifier  [[:alpha:]][[:alnum:]]*
number  0|[1-9][0-9]*

%%

"and"         return AND;
"if"          return IF;
"else"        return ELSE;
"while"       return WHILE;
"read"        return READ;
"write"       return WRITE;
"end"         return END;
"=="          return EQ;
"!="          return NEQ;
"="           return ATTR;
">="          return GE;
">"           return GT;
"<="          return LE;
"<"           return LT;
"+"           return PLUS;
"-"           return MINUS;
"*"           return TIMES;
"/"           return OVER;
";"           return SEMI;
"("           return LPAREN;
")"           return RPAREN;
{number}      { yylval = new_token(); yylval->attr.val = atoi(yytext); return NUM; }
{identifier}  { yylval = new_token(); yylval->attr.name = strdup(yytext); return ID; }
{ws}          /* ignore */;
.	printf("bad input character '%s' at line %d\n", yytext, yylineno);


%%

int yywrap (void) {return 1;}

TreeNode * new_token(void) {
	TreeNode * n = (TreeNode *) malloc(sizeof(TreeNode));
	return n;
}

