/*******************************************************************************************************************************************************************
 * Title        : Common.c  —  Utility Functions for APC (Arbitrary Precision Calculator)
 * Project      : APC - Arbitrary Precision Calculator
 * Developer    : Krishna M
 * Date         : 31/10/2025
 *
 * Description  : This file contains common helper functions used across all arithmetic modules of the APC project.
 *                It provides argument validation, string-to-list conversion, linked list operations, comparison logic,
 *                and formatted output routines. These functions serve as the fundamental building blocks for handling
 *                arbitrary-length integer operations.
 *
 * Core Functionalities:
 *                1. Command-line argument validation and parsing.
 *                2. String-to-doubly-linked-list number conversion.
 *                3. Linked list operations — insertion, deletion, copying, and comparison.
 *                4. Numeric validation for input strings.
 *                5. Even/odd exponent check for power computation.
 *                6. Formatted printing of calculations with right-aligned results.
 *
 * Major Functions:
 *                • Validate_arguments()  → Verifies correct number and format of command-line arguments.
 *                • isNumeric()           → Checks if a given string represents a valid integer.
 *                • String_to_list()      → Converts a numeric string into a doubly linked list of digits.
 *                • Find_largest()        → Compares two number lists and identifies the larger one.
 *                • insert_at_first() / 
 *                  insert_at_last()      → Insert digit nodes at respective ends of a list.
 *                • delete_at_first()     → Removes leading zeros from a result list.
 *                • is_exp_even()         → Determines whether an exponent is even or odd.
 *                • print_calculation()   → Displays formatted arithmetic operation output.
 *
 * Notes         :
 *                • All operations in this file work on magnitudes only — sign management is done in main().
 *                • Input validation ensures program stability and guards against invalid user input.
 *                • Designed for reuse across all APC arithmetic modules.
 *******************************************************************************************************************************************************************/

#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static const char* operators = "+-x^/%";

/* Validate all arguments */
int Validate_arguments( int argc, char* argv[] )
{
    if( argc != 4 )
        return FAILURE;

    if( strchr( operators, argv[2][0] ) == NULL || argv[2][1] != '\0' )
        return FAILURE;
    
    char* str1 = argv[1];
    char* str2 = argv[3];

    if( isNumeric( str1 ) == NON_NUMERIC || isNumeric( str2 ) == NON_NUMERIC )
        return FAILURE;

    return SUCCESS;
}

/* Validate if CLA 2 and 4 are numeric */
int isNumeric(const char *str)
{
    int i = 0;

    if( str[0] == '+' || str[0] == '-' )
        i = 1;

    for( ; str[i] != '\0'; i++)
    {
        if( !isdigit( str[i] ))
            return NON_NUMERIC;   // False
    }

    return NUMERIC;   // True
}

/* Covert the string argument to lists */
void String_to_list( Dlist **head, Dlist **tail, const char *str )
{
    int i = 0;

    if( str[0] == '+' || str[0] == '-' )
    {
        i = 1;
    }

    for( ; str[i] != '\0'; i++ )
    {
        if( insert_at_last( head, tail, str[i] - '0' ) != SUCCESS )
        {
            printf("INFO : Insertion Failure");
            exit(1);
        }
    }
}

// To find largest among 2 number lists
Status Find_largest( Dlist *head1, Dlist *head2 )
{
	int len1 = 0, len2 = 0;
	Dlist *temp1 = head1, *temp2 = head2;

	// Case 1: Using length of numbers
	while( temp1 ) { len1++; temp1 = temp1 -> next; }
	while( temp2 ) { len2++; temp2 = temp2 -> next; }

	if( len1 > len2 ) return LARGE_1;
	if( len2 > len1 ) return LARGE_2;

	// Case 2: Length is equal, check digit wise
	temp1 = head1, temp2 = head2;
	while( temp1 && temp2 )
	{
		if( temp1 -> data > temp2 -> data ) return LARGE_1;
		if( temp1 -> data < temp2 -> data ) return LARGE_2;

		temp1 = temp1 -> next;
		temp2 = temp2 -> next;
	}

	// Case 3: Numbers are equal
	return EQUAL;
}

// Inert a new node at the end of lists
Status insert_at_last( Dlist **head, Dlist **tail, int digit )
{
    Dlist *new = malloc( sizeof( Dlist ));
    if( new == NULL )
    {
        perror("INFO : Memory Allocation Failed");
        return FAILURE;
    }

    new -> data = digit;
    new -> next = NULL;
    new -> prev = NULL;

    if( *head == NULL )
    {
        *head = new;
        *tail = new;

        return SUCCESS;
    }

    (*tail) -> next = new;
    new -> prev = *tail;
    *tail = new;
    
    return SUCCESS;
}

// Insert a new node at the start of lists
Status insert_at_first( Dlist **head, Dlist **tail, int digit )
{
    Dlist *new = malloc( sizeof( Dlist ) );
    if( new == NULL )
        return FAILURE;
    
    new -> data = digit;
    new -> next = NULL;
    new -> prev = NULL;

    if( *tail == NULL )
    {
        *tail = new;
        *head = new;

        return SUCCESS;
    }

    (*head) -> prev = new;
    new -> next = *head;
    *head = new;

    return SUCCESS;
}

// Delete the first node of a list
Status delete_at_first( Dlist **headR, Dlist **tailR )
{
    if( *headR == NULL || *headR == *tailR )
        return SUCCESS;

    while( (*headR) != *tailR && (*headR) -> data == 0 )
    {
        Dlist* temp = *headR;
        *headR = (*headR) -> next;
        (*headR) -> prev = NULL;
        free( temp );
    }

    return SUCCESS;
}

// Check if the exponent is even
Status is_exp_even( Dlist *expH )
{
    Dlist *temp = expH;
    while( temp -> next )
        temp = temp -> next;

    if( ( temp -> data % 2 ) == 0 )
        return EVEN;
    else
        return ODD;
}

// Print the result in formated way and the final sign
void print_calculation( char *num1, char op, char *num2, Dlist *headR, char* final_sign )
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // Count digits in result
    int lenR = 0;
    Dlist *temp = headR;
    while (temp)
    {
        lenR++;
        temp = temp -> next;
    }

    // Find max width for alignment
    int width = len1;
    if ( len2 > width ) width = len2;
    if ( lenR > width ) width = lenR;

    // Print num1
    printf("  %*s\n", width + 1, num1);

    // Print operator left, num2 right aligned
    printf("%c %*s\n", op, width + 1, num2);

    // Print line seperation
    printf(" ");
    for( int i = 0; i <= width + 1; i++ )
        printf("-");
    printf("\n");

    // Print '=' left, result aligned right
    printf("= ");

    // Handle zero alignment separately
    if ( headR && headR -> data == 0 && headR -> next == NULL )
    {
        // result is exactly 0 -> align it to the right edge
        printf("%*c\n", width + 1, '0');
        return;
    }

    // Print Final sign if result is negative
    if( *final_sign == '-' )
        printf("%c", *final_sign);
    else
        printf(" ");

    // Print result (digits from head)
    temp = headR;
    while ( temp )
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}