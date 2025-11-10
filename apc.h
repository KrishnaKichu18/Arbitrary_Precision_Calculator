/*******************************************************************************************************************************************************************
 * File Name    : apc.h
 * Project      : APC - Arbitrary Precision Calculator
 * Date         : 31/10/2025
 *
 * Description  : Header file defining all structures, enumerations, and function prototypes used in the APC project.
 *                This serves as the shared interface for all source modules implementing arbitrary-precision arithmetic
 *                using doubly linked lists. Each function operates on digit-level linked representations to support
 *                calculations on numbers of unlimited size.
 *
 * Purpose      :
 *                • Centralizes all global declarations and data type definitions.
 *                • Ensures modularity and code reusability across the APC codebase.
 *                • Maintains consistent structure and naming across all modules.
 *
 * Notes        :
 *                • The project identity and author details are documented in main.c.
 *                • Sign logic and user interaction are managed externally in main().
 *******************************************************************************************************************************************************************/

#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-------------------------------------------------------------------------------------------------
 * ENUMERATIONS AND TYPE DEFINITIONS
 *------------------------------------------------------------------------------------------------*/
typedef enum
{
    SUCCESS,
    FAILURE,
    NON_NUMERIC,
    NUMERIC,
    LARGE_1,
    LARGE_2,
    EQUAL,
    EVEN,
    ODD
} Status;

typedef int data_t;

/* Doubly Linked List Node Structure */
typedef struct node
{
    struct node *next;
    struct node *prev;
    data_t data;
} Dlist;

/*-------------------------------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *------------------------------------------------------------------------------------------------*/

/* Argument Validation */
int Validate_arguments( int argc , char *argv[] );
int isNumeric( const char *str );

/* List Operations */
Status insert_at_first( Dlist **head, Dlist **tail, int digit );
Status insert_at_last( Dlist **head, Dlist **tail, int digit );
Status delete_at_first( Dlist **headR, Dlist **tailR );
void free_list( Dlist **head, Dlist **tail );
void copy_list( Dlist *srcH, Dlist *srcT, Dlist **dstH, Dlist **dstT );
void Swap_lists( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2 );

/* Utility Functions */
void String_to_list( Dlist **head, Dlist **tail, const char *str );
void subtract_one( Dlist **head, Dlist **tail );
Status Find_largest( Dlist *head1, Dlist *head2 );
Status is_exp_even( Dlist *expH );
Status increment_list( Dlist **head, Dlist **tail );

/* Arithmetic Operations */
Status addition( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR );
Status subtraction( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR );
Status multiplication( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR );
Status division( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR , char* D_or_M );
Status power( Dlist **baseH, Dlist **baseT, Dlist **expH, Dlist **expT, Dlist **headR, Dlist **tailR );

/* Output Function */
void print_calculation( char *num1, char op, char *num2, Dlist *headR, char* final_sign );

#endif /* APC_H */
