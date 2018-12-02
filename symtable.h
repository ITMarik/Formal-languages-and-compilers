
#ifndef  _SYMTABLE_H
#define  _SYMTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    Data_Type type;
    bool defined;   
    char *identifier;
}TData ;

typedef struct TNode {
    char Key;
    TData data;
    struct TNode * LPtr;
    struct TNode * RPtr;
} *NodePtr ;

/*functions*/

void symtable_init (NodePtr *);

TData *symtable_Search (NodePtr *, char K);

void symtable_Insert (NodePtr *,char K, TData Content);

void symtable_Delete (NodePtr *,char K);

void symtable_Free (NodePtr *);

#endif //_SYMTABLE_H
