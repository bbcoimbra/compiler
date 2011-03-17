%option   8bit
%option   warn nodefault
%option   yylineno
%option   outfile="scanner.c" header-file="scanner.h"

%{
#include <string.h>
#include "parser.tab.h"
%}

ws  [[:blank:]\n]*
identifier  [:alpha:][:alnum:]*
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
{number}      { yylval = atoi(yytext); return NUM; }
{identifier}  { yylval = strdup(yytext); return ID; }
{ws}          /* ignore */;
