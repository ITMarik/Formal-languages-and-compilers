
#ifndef  _SYMTABLE_H
#define  _SYMTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct TNode {
    char *Key;
    TData data;
    struct TNode * LPtr;
    struct TNode * RPtr;
} *NodePtr ;

/*functions*/

void symtable_init (NodePtr *);

TNode symtable_Search (NodePtr *RootPtr, char K);

void symtable_Insert (NodePtr *RootPtr,char K, TData Content);

void symtable_Delete (NodePtr *RootPtr,char K);

void symtable_Free (NodePtr *RootPtr);

#endif //_SYMTABLE_H
