/*
 * interpreter.c 
 *
 * Copyright (C) 2012-2013 Peng Jianzhang
 *
 * Author:	Peng Jianzhang
 * Email:	pengjianzhang@gmail.com
 * Time:	2013.3.18
 * */

#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"
#include "list.h"
#include <string.h>

typedef unsigned long u64;

int interpreter_line_num;

void interpreter_err(char * msg)
{
	printf("line %d:%s\n", interpreter_line_num,msg);
} 

static inline int expression_vtype_eq(struct expression_node * en1,struct expression_node * en2)
{
	return (en1->vtype == en2->vtype);
}


void statement_node_init(struct statement_node * sn , enum statement_type t )
{
	sn->stmt_type = t;
	INIT_LIST_HEAD(&(sn->next));	
}

struct statement_node * new_assignment( struct variable * v, struct expression_node * en)
{
	struct assign_statement * as = (struct assign_statement *)malloc(sizeof(struct assign_statement));
	if(as == NULL) return NULL;
	
	if(!expression_vtype_eq(&(v->enode),en))
	{
		interpreter_err("type not match");
		return NULL;
	}	

	as->var = v;
	as->enodep = en;

	return &(as->snode);
}


/* may have problem with string */
struct variable * new_variable(enum value_type  t, u64 value)
{

	struct variable * v = (struct variable * ) malloc(sizeof(struct variable));

	if(v == NULL) return NULL;

	if( t == INTEGER)
	{
		v->v.integer = (long) value;
	}else if( t == BOOLEAN )
	{
		v->v.boolean = (unsigned int)value;
	}
	else if(t == STRING)
	{
		v->v.str.str = (char*)value;
		v->v.str.len = strlen((char*)value);
	}
	else
	{
		free(v);
		v = NULL;
	}

	return v;	
}

/*
 * <operand> 1,2
 * 	 < 0 not care operand 
 * */
static inline int _operation_is_arithmetic(enum operation_type opt, int operand)
{
	if((opt == ADD) || (opt == SUB)||(opt == MUL ) || (opt == DIV) ||(opt == REM) ){
		if((operand == 2) || (operand < 0)) return 1;
		else return 0;
	}
	else 
		return 0;

}

static inline int _operation_is_relation(enum operation_type opt, int operand) 
{
	if( (opt == NE) || (opt == GT) || (opt == LT) ||  (opt ==GE) || (opt ==LE) || (opt ==EQ)){
		if((operand == 2 || operand < 0)) return 1;
		else return 0;	
	}
	else return 0;
}

static inline int _operation_is_logic(enum operation_type opt, int operand) 
{
	if( ((opt == AND) ||  (opt == OR)) && ((operand == 2) || (operand < 0)) )
		return 1;
	else if((opt == NOT) && ((operand == 1) || (operand < 0)))
		return 1;
	else 
		return 0;
}

static inline int _operation_is_unitary( enum operation_type opt)
{
	return (opt == NOT);
}


static inline int _operation_match(enum operation_type opt, enum value_type vt)
{
	if(_operation_is_arithmetic(opt,-1) && (vt ==  INTEGER))
		return 1;	
	else if( _operation_is_relation(opt,-1)&& (vt == INTEGER))
		return 1;
	else if( _operation_is_logic(opt,-1)&&(vt == BOOLEAN) )
		return 1;

	return 0;
}


/*
 * if opt is NE or NOT, en2 == NULL
 *
 * */
struct expression_node * new_expression_node(enum operation_type opt, struct expression_node * en1, struct expression_node * en2)
{
	struct 	expression * e = NULL;

	if(en1 == NULL)
		goto err;
	else if((en2 == NULL) && (!_operation_is_unitary(opt)))
			goto err;
	else if(!expression_vtype_eq(en1,en2))
		goto err;

	if(!_operation_match(opt,en1->vtype)) goto err;

	e = (struct expression *)malloc(sizeof(struct expression));

	if(e == NULL) return NULL;

	if(_operation_is_arithmetic(opt,2)){
		
	}
	else if( _operation_is_relation(opt,2)){

	}
	else if( _operation_is_logic(opt,2)){

	}
	else if( _operation_is_logic(opt,1)){
		
	}
	else
	{
		goto err;
	} 
	
err:
		
	interpreter_err("expression type not match");
	if(e) free(e);
	return NULL;
}



int interpreter_register_functions(struct function_table * ft)
{

}

/* read a script file */

struct script * interpreter_read_file(char * filename)
{

}

/***execute a script **/



int interpreter_run(struct script * s)
{

/*
	for each statements
	{
		ret = 	_do_statements 
		
		if(ret )
	}
*/

	return 1;
}




/*****execute statements**/


static int _do_statements ()
{


	return 0;
}
