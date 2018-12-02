#ifndef  _BSTSYMTABLE_H
#define  _BSTSYMTABLE_H

#include <stdbool.h>

// #include "dynamic_string"

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
    // Dynamic_string *params;     //params in string for TO DO
    char *identifier;
}TData ;

typedef struct tBSTsymtable {
    char Key;
    TData data;
    struct tBSTsymtable * LPtr;
    struct tBSTsymtable * RPtr;
} *tBSTNodePtr ;

/*functions*/

/**
 * Function initializes BStree
 *
 * @param tBSTNodePtr pointer to root of tree
 */
void BST_symtable_init (tBSTNodePtr *);

/**
 * Function finds symbol and returns its data node
 *
 * @param tBSTNodePtr pointer to root of tree
 * @param K Node Identifier
 * @return NULL if symbol doesnt exist or pointer to Data node
 */
TData *BST_symtable_Search (tBSTNodePtr *, char K);

/**
 * Function Appends symbol to the BStree
 *
 * @param tBSTNodePtr pointer to root of tree
 * @param K Node Identifier
 * @param Content Node Content
 * @return 1 if succesful 0 if not
 */
bool BST_symtable_Insert (tBSTNodePtr *,char K, TData Content);

/**
 * Function Deletes symbol node from BStree
 * @param tBSTNodePtr pointer to root of tree
 * @param K Node Identifier
 * @return 1 if succesful 0 if not
 */
bool BST_symtable_Delete (tBSTNodePtr *,char K);

/**
 * Function frees all resources allocated for BStree
 *
 * @param tBSTNodePtr pointer to root of tree
 */
void BST_symtable_Free (tBSTNodePtr *);

#endif //_BSTSYMTABLE_H
