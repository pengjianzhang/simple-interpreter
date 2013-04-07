%{
#include "interpreter.tab.h"
%}
		
lex_num		[1-9][0-9]+
lex_vsymbol	[A-Z][a-zA-Z0-9_]*
lex_fsymbol	[a-z][a-zA-Z0-9_]*
lex_string		([^ \t\n]+)|(\"(.|\\\")*\")
lex_comment0	#[^\n]*
lex_comment1	"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" 	


%%


"if"		{return IF;}
"else"		{return ELSE;}
"elsif"		{return ELSIF;}
"return"	{ return RETURN;}	

">"		{ return OP_GT;}
"<"		{ return OP_LT;}
">="		{ return OP_GE;}
"<="		{return OP_LE;}
"=="

"&&"		{ return OP_AND;}
"||"		{ return OP_OR;}
"!"		{ return OP_NOT;}
"\n"		{interpreter_line_num++;}

{lex_num}		{ yylval.num = atoi(yytext); return NUM;}
{lex_vsymbol}		{ yylval.str = strdup(yytext); return VSYMBOL;}	
{lex_fsymbol}		{ yylval.str = strdup(yytext); return FSYMBOL;}
{lex_string}		{ yylval.str = strdup(yytext); return STRING;}
lex_comment0		{;}
lex_comment1		{;}
.			{return yytext[0];}

