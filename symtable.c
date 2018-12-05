/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        symtable.c - implementace tabulky symbolů            *
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Členové týmu :  Martin Janda                                         *
 *              :  Marek Šťastný                                        *
 *              :  Martina Tučková                                      *
 *              :  Martina Jendrálová                                   *
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/


#include "symtable.h"

void symtable_init (NodePtr *RootPtr){

    *RootPtr = NULL;
}

void symtable_Insert (NodePtr *RootPtr,char K, TData Content){
    
    if (*RootPtr == NULL) {
    	*RootPtr = malloc(sizeof(struct TNode));
		if (RootPtr == NULL)
            return;
        (*RootPtr)->LPtr = NULL;
        (*RootPtr)->RPtr = NULL;
        (*RootPtr)->Key = K;
        (*RootPtr)->data = Content;
    }
    else if ((*RootPtr)->Key > K)
        symtable_Insert (&(*RootPtr)->LPtr, K, Content);
    else if ((*RootPtr)->Key < K)
        symtable_Insert (&(*RootPtr)->RPtr, K, Content);
    else
        (*RootPtr)->data = Content;
}


TData *symtable_Search (NodePtr *RootPtr, char K){
    if(RootPtr != NULL){
        if((*RootPtr)->Key == K){
            return &(*RootPtr)->data;
        }
        else{
            if((*RootPtr)->Key > K)
                return symtable_Search(&((*RootPtr)->LPtr), K);
            else
                return symtable_Search(&((*RootPtr)->RPtr), K);
        }
    }
    else{
        return NULL;
    }
}


void ReplaceByRightmost (NodePtr PtrReplaced, NodePtr *RootPtr){
    if(*RootPtr != NULL)
    {
        if((*RootPtr)->RPtr != NULL)
        {
            ReplaceByRightmost(PtrReplaced, &(*RootPtr)->RPtr);
        }
        else
        {
            PtrReplaced->Key = (*RootPtr)->Key;
            PtrReplaced->data = (*RootPtr)->data;
            NodePtr helpling = *RootPtr;
            *RootPtr = (*RootPtr)->LPtr;
            free(helpling);
        }
    }
}


void symtable_Delete (NodePtr *RootPtr, char K) {
    
    if(*RootPtr != NULL){
        if((*RootPtr)->Key < K)
            symtable_Delete(&(*RootPtr)->RPtr, K);
        else if((*RootPtr)->Key > K)
            symtable_Delete(&(*RootPtr)->LPtr, K);
        else{
            NodePtr helpling = *RootPtr;
            if(helpling->LPtr == NULL){
                *RootPtr = helpling->RPtr;
                free(helpling);
            }
            else if(helpling->RPtr == NULL){
                *RootPtr = helpling->LPtr;
                free(helpling);
            }
            else
                ReplaceByRightmost (*RootPtr, (&(*RootPtr)->LPtr));
        }
    }
}


void symtable_Free (NodePtr *RootPtr){
    if(*RootPtr != NULL)
    {
        symtable_Free(&(*RootPtr)->LPtr);
        symtable_Free(&(*RootPtr)->RPtr);
        free(*RootPtr);
        *RootPtr = NULL;
    }
}
