# Compiler (Language has no name yet!)

This project is under development as a proof of concept of my
degree thesis for Data Processing Technologist for FATEC-SP
in Brazil.

	*Disclaimer*: There are lots of bugs and untested scenarios.

## Compiling

Project uses autotools for building and distribution. So you
just need to clone this repository and execute in your shell:

	$ ./configure && make

If compilations runs ok, a binary named compiler will be placed
at src/ directory.

## Usage

	compiler [-t] [-s] [-c file_name] input_file

## Grammar Recognized

Follow grammar is recognized:

	stmts : stmts stmt
				| stmt
				;

	stmt  : if_decl SEMI
				| while_decl SEMI
				| attrib_decl SEMI
				| read_decl SEMI
				| write_decl SEMI
				;

	if_decl  : IF LPAREN bool RPAREN stmts END
					 | IF LPAREN bool RPAREN stmts ELSE stmts END
					 ;

	while_decl : WHILE LPAREN bool RPAREN stmts END
						 ;

	attrib_decl : ID
							ATTR expr
							;

	read_decl : READ ID
						;

	write_decl : WRITE ID
						 ;

	expr : expr PLUS expr
			 | expr MINUS expr
			 | expr TIMES expr
			 | expr OVER expr
			 | factor
			 | bool
			 ;

	bool : expr OR expr
			 | expr AND expr
			 | expr EQ expr
			 | expr NEQ expr
			 | expr GT expr
			 | expr LT expr
			 | expr GE expr
			 | expr LE expr
			 | expr
			 ;

	factor : LPAREN expr RPAREN
				 | ID
				 | NUM
         ;

Terminals are that written in uppercase and their tokens are described in
_src/scanner.l_. For now, tokens that represent key words are lowercase
words but written in Portuguese, e. g. IF, WHILE are "se", "enquanto",
respectively. LPAREN and RPAREN means "(" and ")", SEMI means ";".
Mathematical names means their usual symbols, e. g. PLUS means "+".
Same rule is applyed to comparisons, e. g., EQ means "==" and GT means ">".
IDs are string identifiers (a.k.a. variables) and NUMs are numeric integral
constants.


