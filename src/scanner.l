%{
#include "parser.h"
#include <string.h>
#include "global.h"
#include "util.h"
%}

%option 8bit bison-bridge
%option warn nodefault
%option yylineno noyywrap
%option outfile="scanner.c" header-file="scanner.h"

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
{number}      {yylval.num = atoi(yytext); return NUM;}
{identifier}  {yylval.name = strdup(yytext); return ID; }
{ws}          /* ignore */;
.	printf("bad input character '%s' at line %d\n", yytext, yylineno);

