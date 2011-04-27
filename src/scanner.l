%{
#include "compiler-parser.h"
#include <string.h>
#include "global.h"
#include "util.h"
extern YYSTYPE yylval;
%}

%option 8bit
%option warn nodefault
%option yylineno noyywrap

ws  [[:blank:]\n]*
identifier  [[:alpha:]][[:alnum:]]*
number  0|[1-9][0-9]*

%%

"e"           return AND;
"ou"          return OR;
"se"          return IF;
"senao"       return ELSE;
"enquanto"    return WHILE;
"leia"        return READ;
"escreva"     return WRITE;
"fim"         return END;
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
{number}      {
                yylval.token = new_token();
								(yylval.token)->value.val = atoi(yytext);
                return NUM;
              }
{identifier}  {
                yylval.token = new_token();
								(yylval.token)->value.name = copy_str (yytext);
								(yylval.token)->lineno = yylineno;
                return ID;
              }
{ws}          /* ignore */;
.             printf("bad input character '%s' at line %d\n", yytext, yylineno);

