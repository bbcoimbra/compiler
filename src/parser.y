%token AND ATTR ELSE END EQ GE GT ID IF LE LPAREN LT ;
%token MINUS NEQ NUM OR OVER PLUS READ RPAREN SEMI TIMES ;
%token WHILE WRITE ERROR ;

%left LPAREN;
%left TIMES OVER;
%left PLUS MINUS;
%left GE GT LE LT;

%%

stmts       : stmts SEMI stmt
						| stmt
						;

stmt        : if_decl
						| while_decl
						| attrib_decl
						| read_decl
						| write_decl
						| expr
						;

if_decl     : IF LPAREN bool RPAREN stmts END
						| IF LPAREN bool RPAREN stmts ELSE stmts END
						;

while_decl  : WHILE LPAREN bool RPAREN stmts END
						;

attrib_decl : ID ATTR expr
						;

read_decl   : READ ID
						;

write_decl  : WRITE ID
						;

expr        : expr PLUS term
						| expr MINUS term
						| term
						;

bool				: bool OR join
						| join
						;

join				: join AND equality
						| equality
						;

equality		: equality EQ rel
						| equality NEQ rel
						| rel
						;

rel					: expr GT expr
						| expr LT expr
						| expr GE expr
						| expr LE expr
						| expr
						;

term				: term TIMES factor
						| term OVER factor
						| factor
						;

factor			: LPAREN expr RPAREN
						| ID
						| NUM
						| LPAREN bool RPAREN
						;

