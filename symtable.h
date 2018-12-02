#ifndef  _SYMTABLE_H
#define  _SYMTABLE_H

#include <stdbool.h>

typedef enum {
    TYPE_UNDEFINED,
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_BOOL,
}Data_Type ;

typedef struct {
    Data_Type type;
    bool defined;   
    char *identifier;
}TData ;

typedef struct tBSTsymtable {
    char Key;
    TData data;
    struct tBSTsymtable * LPtr;
    struct tBSTsymtable * RPtr;
} *tBSTNodePtr ;

/*functions*/

void symtable_init (tBSTNodePtr *);

TData *symtable_Search (tBSTNodePtr *, char K);

bool symtable_Insert (tBSTNodePtr *,char K, TData Content);

bool symtable_Delete (tBSTNodePtr *,char K);

void symtable_Free (tBSTNodePtr *);

#endif //_BSTSYMTABLE_H
