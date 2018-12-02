    
#include <stdlib.h>
#include <stdio.h>

#include "symtable.h"

void symtable_init (tBSTNodePtr *RootPtr){

    if (RootPtr == NULL)
        return;
    *RootPtr = NULL;
}

void symtable_Insert (tBSTNodePtr *RootPtr,char K, TData Content){
    
    if (!(*RootPtr)) {
        if (!(*RootPtr = malloc (sizeof(struct tBSTNode))))
            return;
        (*RootPtr)->LPtr = NULL;
        (*RootPtr)->RPtr = NULL;
        (*RootPtr)->Key = K;
        (*RootPtr)->BSTNodeCont = Content;
    }
    else if ((*RootPtr)->Key > K)
        symtable_Insert (&(*RootPtr)->LPtr, K, Content);
    else if ((*RootPtr)->Key < K)
        symtable_Insert (&(*RootPtr)->RPtr, K, Content);
    else
        (*RootPtr)->BSTNodeCont = Content;
}


TData *symtable_Search (tBSTNodePtr *RootPtr, char K){
    if(RootPtr != NULL){
        if((*RootPtr)->Key == K){
            return &(*RootPtr)->data;
        }
        else{
            if((*RootPtr)->Key > K){
                return BST_symtable_Search(&((*RootPtr)->LPtr), K);
            }
            else{
                return BST_symtable_Search(&((*RootPtr)->RPtr), K);
            }
        }
    }
    else{
        return NULL;
    }
}


void ReplaceByRightmost (tBSTNodePtr PtrReplaced, tBSTNodePtr *RootPtr){
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
            tBSTNodePtr helpling = *RootPtr;
            *RootPtr = (*RootPtr)->LPtr;
            free(helpling);
        }
    }
}


bool symtable_Delete (tBSTNodePtr *RootPtr, char K){
    if(*RootPtr != NULL){
        if((*RootPtr)->Key < K){
            BST_symtable_Delete(&(*RootPtr)->RPtr, K);
        }
        else if((*RootPtr)->Key > K){
            BST_symtable_Delete(&(*RootPtr)->LPtr, K);
        }
        else{
            tBSTNodePtr helpling = *RootPtr;
            if(helpling->LPtr == NULL){
                *RootPtr = helpling->RPtr;
                free(helpling);
            }
            else if(helpling->RPtr == NULL){
                *RootPtr = helpling->LPtr;
                free(helpling);
            }
            else{
                ReplaceByRightmost (*RootPtr, (&(*RootPtr)->LPtr));
            }
        }
        return true;
    }
    else{
        return false;
    }
}


void symtable_Free (tBSTNodePtr *RootPtr){
    if(*RootPtr != NULL)
    {
        BST_symtable_Free(&(*RootPtr)->LPtr);
        BST_symtable_Free(&(*RootPtr)->RPtr);
        free(*RootPtr);
        *RootPtr = NULL;
    }
}