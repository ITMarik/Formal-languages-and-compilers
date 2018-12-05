/************************************************************************
 * Předmět:        IFJ / IAL                                            *
 * Soubor :        generator.c - vlastní generování, 3 adresný kód      *
 * Datum :         5.12. 2018                                           *
 * Projekt :       Implementace překladače imperativního jazyka IFJ 18  *
 * Členové týmu :  Martin Janda                                         *
 *              :  Marek Šťastný                                        *
 *              :  Martina Tučková                                      *
 *              :  Martina Jendrálová                                   *
 * Varianta :      Tým 123, varianta I                                  *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

FILE *generator_result;

int create_something (assembler_calling magic, char *sym1, char *sym2, char *sym3) {


    //lets get the party started

  if (sym1 == NULL && sym2 == NULL && sym3 == NULL) {     // this case means i have no operands at all, im *ucked up
    switch (magic) {

      // instructions which may work without operands
      case CREATEFRAME:
        fprintf(generator_result, "%s\n", "CREATEFRAME"); break;
      case PUSHFRAME:
        fprintf(generator_result, "%s\n", "PUSHFRAME"); break;
      case POPFRAME:
        fprintf(generator_result, "%s\n", "POPFRAME"); break;
      case RETURN:
        fprintf(generator_result, "%s\n", "DEFVAR"); break;
      case CLEARS:
        fprintf(generator_result, "%s\n", "CLEARS"); break;
      case ADDS:
        fprintf(generator_result, "%s\n", "ADDS"); break;
      case SUBS:
        fprintf(generator_result, "%s\n", "SUBS"); break;
      case MULS:
        fprintf(generator_result, "%s\n", "MULS"); break;
      case DIVS:
        fprintf(generator_result, "%s\n", "DIVS"); break;
      case IDIVS:
        fprintf(generator_result, "%s\n", "IDIVS"); break;
      case LTS:
        fprintf(generator_result, "%s\n", "LTS"); break;
      case GTS:
        fprintf(generator_result, "%s\n", "GTS"); break;
      case EQS:
        fprintf(generator_result, "%s\n", "EQS"); break;
      case ANDS:
        fprintf(generator_result, "%s\n", "ANDS"); break;
      case ORS:
        fprintf(generator_result, "%s\n", "ORS"); break;
      case NOTS:
        fprintf(generator_result, "%s\n", "NOTS"); break;
      case INT2FLOATS:
        fprintf(generator_result, "%s\n", "INT2FLOATS"); break;
      case FLOAT2INTS:
        fprintf(generator_result, "%s\n", "FLOAT2INTS"); break;
      case INT2CHARS:
        fprintf(generator_result, "%s\n", "INT2CHARS"); break;
      case STRI2INTS:
        fprintf(generator_result, "%s\n", "STRI2INTS"); break;
      case BREAK:
        fprintf(generator_result, "%s\n", "BREAK"); break;
    } 
  }

  if (sym1 != NULL && sym2 == NULL && sym3 == NULL) {     // this case means i have one operand, sym1

    switch (magic) {

      case DEFVAR:
        fprintf(generator_result, "%s %s\n", "DEFVAR", sym1); break;
      case CALL:
        fprintf(generator_result, "%s %s\n", "CALL", sym1); break;
      case PUSHS:
        fprintf(generator_result, "%s %s\n", "PUSHS", sym1); break;
      case POPS:
        fprintf(generator_result, "%s %s\n", "POPS", sym1); break;
      case WRITE:
        fprintf(generator_result, "%s %s\n", "WRITE", sym1); break;
      case LABEL:
        fprintf(generator_result, "%s %s\n", "LABEL", sym1); break;
      case JUMP:
        fprintf(generator_result, "%s %s\n", "JUMP", sym1); break;
      case JUMPIFEQS:
        fprintf(generator_result, "%s %s\n", "JUMPIFEQS", sym1); break;
      case JUMPIFNEQS:
        fprintf(generator_result, "%s %s\n", "JUMPIFNEQS", sym1); break;
      case EXIT:
        fprintf(generator_result, "%s %s\n", "EXIT", sym1); break;
      case DPRINT:
        fprintf(generator_result, "%s %s\n", "DPRINT", sym1); break;
    }
  }

  if (sym1 != NULL && sym2 != NULL && sym3 == NULL) {     // this case means i have two operands ... it's getting hot

    switch (magic) {

      case MOVE:
        fprintf(generator_result, "%s %s %s\n", "MOVE", sym1, sym2); break;
      case INT2FLOAT:
        fprintf(generator_result, "%s %s %s\n", "INT2FLOAT", sym1, sym2); break;
      case FLOAT2INT:
        fprintf(generator_result, "%s %s %s\n", "FLOAT2INT", sym1, sym2); break;
      case INT2CHAR:
        fprintf(generator_result, "%s %s %s\n", "INT2CHAR", sym1; sym2); break;
      case READ:
        fprintf(generator_result, "%s %s %s\n", "READ", sym1, sym2); break;
      case STRLEN:
        fprintf(generator_result, "%s %s %s\n", "STRLEN", sym1, sym2); break;
      case TYPE:
        fprintf(generator_result, "%s %s %s\n", "TYPE", sym1, sym2); break;
    }
  }

    if (sym1 != NULL && sym2 != NULL && sym3 != NULL) {     // now i have all 3 operands ... i'm done

      switch (magic) {

        case ADD:
          fprintf(generator_result, "%s %s %s %s\n", "ADD", sym1, sym2, sym3); break;
        case SUB:
          fprintf(generator_result, "%s %s %s %s\n", "SUB", sym1, sym2, sym3); break;
        case MUL:
          fprintf(generator_result, "%s %s %s %s\n", "MUL", sym1, sym2, sym3); break;
        case DIV:
          fprintf(generator_result, "%s %s %s %s\n", "DIV", sym1, sym2, sym3); break;
        case IDIV:
          fprintf(generator_result, "%s %s %s %s\n", "IDIV", sym1, sym2, sym3); break;
        case LT:
          fprintf(generator_result, "%s %s %s %s\n", "LT", sym1, sym2, sym3); break;
        case GT:
          fprintf(generator_result, "%s %s %s %s\n", "GT", sym1, sym2, sym3); break;
        case EQ:
          fprintf(generator_result, "%s %s %s %s\n", "EQ", sym1, sym2, sym3); break;
        case AND:
          fprintf(generator_result, "%s %s %s %s\n", "AND", sym1, sym2, sym3); break;
        case OR:
          fprintf(generator_result, "%s %s %s %s\n", "OR", sym1, sym2, sym3); break;
        case NOT:
          fprintf(generator_result, "%s %s %s %s\n", "NOT", sym1, sym2, sym3); break;
        case STRI2INT:
          fprintf(generator_result, "%s %s %s %s\n", "STRI2INT", sym1, sym2, sym3); break;
        case CONCAT:
          fprintf(generator_result, "%s %s %s %s\n", "CONCAT", sym1, sym2, sym3); break;
        case GETCHAR:
          fprintf(generator_result, "%s %s %s %s\n", "GETCHAR", sym1, sym2, sym3); break;
        case SETCHAR:
          fprintf(generator_result, "%s %s %s %s\n", "SETCHAR", sym1, sym2, sym3); break;
        case JUMPIFEQ:
          fprintf(generator_result, "%s %s %s %s\n", "JUMPIFEQ", sym1, sym2, sym3); break;
        case JUMPIFNEQ:
          fprintf(generator_result, "%s %s %s %s\n", "JUMPIFNEQ", sym1, sym2, sym3); break;
      }
    }  

    return vypis_hodnotu(0);  
} 