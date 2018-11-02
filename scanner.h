#include <error_h.h>

#ifndef SCANNER_H
#define SCANNER_H

typedef enum {
	//list of all possible tokens named by their role

	//file asociated tokens
	TOKEN_EndOfFile;			//file has ended
	TOKEN_EndOfLine;			//line has ended - "\n"
	
	//mathematical operating asociated tokens
	Token_minus;				//operation of +
	Token_plus;					//operation of -
	Token_division;				//operation of /
	Token_multiply;				//operation of *
	
	//boolean asociated tokens
	Token_less;					//operation of <
	Token_less_equal;			//operation of <=
	Token_greater;				//operation of >
	Token_greater_equal;		//operation of >=
	Token_equal;				//operation of ==
	Token_not_equal;			//operation of !=

}	token_t;

typedef struct {
	token_t type;  				//load our tokens and give them their actual type
} token;

int get_token(token *load);

#endif
