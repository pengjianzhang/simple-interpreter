/*
 * interpreter.h 
 *
 * Copyright (C) 2012-2013 Peng Jianzhang
 *
 * Author:	Peng Jianzhang
 * Email:	pengjianzhang@gmail.com
 * Time:	2013.4.2
 * */



#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "list.h"

enum expression_type
{
	VARIABLE_EXPR,		/* a variable */
	ARITHMETIC_EXPR,	/* V1 + V2, + - * / % */
	FUNCTION_EXPR,		/* string.len(Var) */
	LOGIC_EXPR,		/* (RELATION_EXPR) && ( RELATION_EXPR ) */	
	RELATION_EXPR,		/* V1 >= V2, > < >= <= == != */	
};

enum value_type
{
	INTEGER,
	BOOLEAN,
	STRING,
};


enum operation_type
{

	ADD,	/* + */
	SUB,	/* - */
	MUL,	/* * */
	DIV,	/* / */
	REM,	/* % */
	

	GT,	/* > */	
	LT,	/* < */	
	GE,	/* >= */	
	LE,	/* <= */	
	EQ,	/* == */	
	NE,	/* != */	

	AND ,	/* && */	
	OR ,	/* || */	
	NOT ,	/* ! */	
	
	CALL,	/* function call */

	NO_OP,	/* a variable */	
};

/* how to deal with string
 *
 *
 * */

struct bg_string
{
	char * str;
	int len;
	unsigned char cflag;
};


struct expression_node 
{
//	enum expression_type etype;
	enum value_type	vtype;	
	enum operation_type optype;	
};



struct variable
{
	struct expression_node enode;

	union
	{
		struct bg_string str;
		long integer;	
		unsigned int boolean;
	}v;
};	

struct expression
{
	struct expression_node enode;
	struct expression_node * op[2];	
};


enum statement_type
{
	ASSIGN_STMT,
	IFELSE_STMT,	/* IF , IF ELSE, IF ELSIF() */
	FUNCTION_STMT,	
	RETURN_STMT,	
};

/*******************/

struct statement_node
{
	enum statement_type stmt_type;	
	struct list_head next;		/* link all statement in a script */		
};



struct assign_statement
{
	struct statement_node snode;
	struct variable * var;
	struct expression_node * enodep;
};


struct ifbranch
{
	struct statement_node snode;
	struct variable * var;
	struct expression * expr;
	struct statement * stmt;
};

/*
 *malloc(sizeof(struct ifelse_statement) + len*sizeof(struct ifcase));
 * */

struct ifelse_statement
{
	struct statement_node snode;
	struct variable * var;
	int num;
	struct ifbranch branch[0];
};


struct function_call
{
	struct expression_node expr;
	void * fun_addr;		
	int num;
	struct expresstion * argv[0];	
};

/*
 * f();
 *  not include A = f();this is a  assignment
 * */
struct function_statement
{
	struct statement_node snode;
	struct function_call fcall;
};


#define MAX_SCRIPT_NAME	64
struct script
{
	char  name[MAX_SCRIPT_NAME];
	struct list_head stmt;	
	struct variable  varspace[0];
};


#define MAX_ARGUMENT_NUM	16	
#define MAX_FUNCTION_NAME	32	
#define MAX_CLASS_NAME		32

/*
 * eg string.len
 *
 * <len> is a function 
 * the entry like this
 * 	fname 	: "len"
 *	fixargc	: 1
 *	is_variable_parameters:0
 *	type[0] : STRING	
 * */
struct function_entry
{
	char  fname[MAX_FUNCTION_NAME];
	int fixargc;			/**/		
	int is_variable_parameters_flag; 	/**/ 
	enum value_type vtype[MAX_ARGUMENT_NUM];
};


/*
 * string is a class, all string functions in a function_table
 *
 * */
struct function_class
{
	struct list_head list;
	char classname[MAX_CLASS_NAME];
	int len;
	struct function_entry fentry[0];	
};


struct simple_interpreter
{
	struct list_head script_list;
	struct list_head function_table_list;
};




extern int interpreter_line_num;






#endif
