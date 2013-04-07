%{

#include "interpreter.h"


%}

%union  {
	long	num;
	char * str;	
}


%token	NUMBER	STRING	VSYMBOL	 FSYMBOL IF ELSE ELSIF	RETURN OP_GT OP_LT OP_GE OP_LE OP_EQ OP_AND OP_OR OP_NOT


/* %right  */
%left '-' '+'
%left '*' '%' '/'
%left '!'


STATEMENT_LIST	: STATEMENT	{$$ = $1;}
		| STATEMENT_LIST STATEMENT	{list_add_tail(&($2->next), &($1->next)); $$ = $1;}
		;


STATEMENT	: ASSIGN_STATEMENT	{ $$ = $1;}
		| IFELSE_STATEMENT	{$$ = $1;}
		| FUNCTION_STATEMENT	{$$ = $1;}
		| RETURN_STATEMENT	{$$ = $1;}
		;

ASSIGN_STATEMENT	: VARIABLE '=' EXPRESSION ';' { $$ = new_assignment( $1, $3);}
			;


EXPRESSION	: EXP1 				{$$=$1;}
		| EXP1 OP2 EXP1 		{ ;}	
/*
		| EXP1 OP2 '(' EXPRESSION ')'	{ ;}
		| '(' EXPRESSION ')' OP2 EXP1	{ ;}
		| '(' EXPRESSION ')'		{ ;}	
		| OP_NOT '(' EXPRESSION ')'	{ ;}	
	*/	;	
	
OP2	: '+'	{}
	| '-'	{}	
	| '*'	{}
	| '/'	{}
	| OP_GT	{}
	| OP_GE	{}
	| OP_LT	{}	
	| OP_LE	{}
	| OP_EQ	{}
	| OP_AND	{}
	| OP_OR		{}
	;	

EXP1	: VARIABLE	{ }
	| FUNCTION_EXPRESSION	{}
	;	

VARIABLE	:	NUMBER		{}
		| '-' 	NUMBER		{} 	
		|	STRING		{}
		|	VSYMBOL		{}
		;


FUNCTION_STATEMENT	: FUNCTION_EXPRESSION ';'
			;

FUNCTION_EXPRESSION	: FSYMBOL '.' FSYMBOL '(' ARGLIST ')'	{}		
			| FSYMBOL '.' FSYMBOL '('  ')'		{}
			;				

ARGLIST	:	EXPRESSION		{}
	| ARGLIST ',' EXPRESSION	{}
	;

RETURN_STATEMENT	:	RETURN ';'	{}
			;

IFELSE_STATEMENT	:  IF_BLOCK	{}
			| IF_BLOCK ELSE_BLOCK	{}
			| IF_BLOCK ELSIF_LIST 	{}
			| IF_BLOCK ELSIF_LIST ELSE_BLOCK {} 
			;


IF_BLOCK	: IF '(' EXPRESSION ')' '{' STATEMENT_LIST '}' {}
		;
ELSE_BLOCK	: ELSE '{' STATEMENT_LIST '}' {}
		;

ELSIF_BLOCK	: ELSIF '(' EXPRESSION ')' '{' STATEMENT_LIST '}'	{}
		;

ELSIF_LIST	: ELSIF_BLOCK	{}
		|  ELSIF_LIST ELSIF_BLOCK {}
		;


%%



%%

extern char * yytext;

int yyerror(char *str)
{
        fprintf(stderr,"Error: %s\n",str);
	printf("yytext:%s\n",yytext);
        return 1;
 }

int yywrap()
{
         return 1;
}


