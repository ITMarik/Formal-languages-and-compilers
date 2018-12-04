#ifndef GENERATOR_H
#define GENERATOR_H

typedef enum {

	//work with frames a function calls
	MOVE,  // <var> <symb>   cp <symb> to <var>
	CREATEFRAME,   	//create new frame, dleete the old one
	PUSHFRAME,    	//if fail, then call error(55)
	POPFRAME,		//if fail, then call error(55)
	DEFVAR,			//  <var> define variable
	CALL,			//  <label> save actual position of of internal compiler
	RETURN,			//  pin out position of stack a jump to position

	//workwith data stack
	PUSHS,			//  <symb> save value to stack
	POPS,			//  <var> if stack != empty, take its value and save to var
	CLEARS,			//  clear stack to not recognize old values

	//arithmetical, relatives, boolean a conversion instructions
	ADD,			//  <var> <symb1> <symb2> count symb1 and symb2 and save to var
	SUB, 			// 	<var> <symb1> <symb2> sub symb1 and symb2 and save to var
	MUL,			//  <var> <symb1> <symb2> mul - || - 
	DIV,			// 	<var> <symb1> <symb2> div - || -
	IDIV,			//  <var> <symb1> <symb2> div with int number !! rest is same
	
	ADDS, SUBS, MULS, DIVS, IDIVS,  //stack versions of add, sub, mul, div and idiv
	
	LT, GT, EQ, 					// <var> <symb1> <symb2>	relative operators
	
	LTS, GTS, EQS,					//stack versions of lt, gt, eq
	
	AND, OR, NOT,					// <var> <symb1> <symb2>   just logical operators - conjuction and so on ... 
	
	ANDS, ORS, NOTS,				//	stack version of add, or, not		
	
	INT2FLOAT,		//	<var> <symb>  convert int number to float number and save in var  
	FLOAT2INT,		// 	<var> <symb>  convert float number to int number and save to var 
	INT2CHAR,		//	<var> <symb>  int number is by ASC converted to char and saved in var
	STRI2INT,		//	<var> <symb1> <symb2>  save in var ord. value from string <symb1> on position <symb2>
	
	INT2FLOATS, FLOAT2INTS, INT2CHARS, STRI2INTS,	// stack versions of convertin operations

	//input - output instructions
	READ,			//	<var> <type>  
	WRITE,			// 	<symb>

	//work with strings
	CONCAT,			//  <var> <symb1> <symb2>  save to var string concatenation of symb1 and symb2  
	STRLEN,			//  <var> <symb>   find out str length
	GETCHAR,		//  <var> <symb1> <symb2>  
	SETCHAR,		//  <var> <symb1> <symb2> 

	//work with types
	TYPE, 			// 	<var> <symb> 

	//instrutions for flow controll in our compiler
	LABEL,			// 	<label>
	JUMP,			//  <label>
	JUMPIFEQ,		//  <label> <symb1> <symb2>
	JUMPIFNEQ,		// 	<label> <symb1> <symb2> 
	JUMPIFEQS,JUMPIFNEQS,	//  <label>
	EXIT,			//  <symb>

	//debug instructions
	BREAK,
	DPRINT			//  <symb>
} assembler_calling;

//int (assembler_calling some_shit, char *sym1, char *sym2, char *sym3)

#endif