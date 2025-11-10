/*******************************************************************************************************************************************************************
 * Function Name    : division
 * Description      : Performs integer division or modulus operation on two large positive numbers represented as doubly linked lists.
 *                    Each node stores a single digit, with the head being the Most Significant Digit (MSD) and the tail being the
 *                    Least Significant Digit (LSD). The function handles division by zero, magnitude comparison, and repeated
 *                    subtraction-based division while maintaining the result as an arbitrary-precision number list.
 *
 * Prototype        : Status division( Dlist **head1, Dlist **tail1,
 *                                     Dlist **head2, Dlist **tail2,
 *                                     Dlist **headR, Dlist **tailR,
 *                                     char *D_or_M );
 *
 * Input Parameters : head1, tail1 -> Pointers to the head and tail of the dividend number list.
 *                    head2, tail2 -> Pointers to the head and tail of the divisor number list.
 *                    headR, tailR -> Pointers to the head and tail of the result number list (initially empty).
 *                    D_or_M       -> String indicator specifying operation type:
 *                                      "Div" → Compute and return the quotient.
 *                                      "Mod" → Compute and return the remainder.
 *
 * Return Value     : SUCCESS -> Division or modulus completed successfully.
 *                    FAILURE -> If subtraction or node allocation fails during the process.
 *
 * Special Cases    :
 *                    • Divisor = 0 → Displays error and terminates program (division undefined).
 *                    • Dividend < Divisor → Quotient = 0, Remainder = Dividend.
 *                    • Dividend = Divisor → Quotient = 1, Remainder = 0.
 *
 * Algorithm        :
 *                    1. Check for divide-by-zero and terminate safely if detected.
 *                    2. Compare dividend and divisor:
 *                         - If equal, directly assign result (1 for division, 0 for modulus).
 *                         - If smaller, quotient = 0 or remainder = dividend.
 *                    3. Otherwise, perform repeated subtraction:
 *                         - Subtract divisor from dividend until dividend < divisor.
 *                         - Use increment_list() to maintain an arbitrary-precision quotient.
 *                    4. After the loop:
 *                         - For "Div" → Copy the quotient list into the result.
 *                         - For "Mod" → Copy the remaining dividend into the result.
 *                    5. Remove any leading zeros from the result list.
 *                    6. Free temporary quotient list memory.
 *
 * Notes            :
 *                    • This function handles only positive integer division; sign determination is managed externally.
 *                    • The quotient and remainder are both represented as Dlists for arbitrary-precision results.
 *******************************************************************************************************************************************************************/

#include "apc.h"

Status division( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR , char* D_or_M )
{

	// Check if divisor is zero
	if( (*head2) -> data == 0 && !(*head2) -> next )
	{
		printf("INFO: Division by Zero is not possible\n");
		exit(0);
	}

	// Get the largest number
	Status large = Find_largest( *head1, *head2 );
	
	// If both numbers are equal return 1
	if( large == EQUAL )
	{
		if( strstr( D_or_M, "Div" ) )
			insert_at_last( headR, tailR, 1 ); // Quotient is 1

		else
			insert_at_last( headR, tailR, 0 ); // Reminder is 0

		return SUCCESS;
	}

	// If divident < divisor
	if( large == LARGE_2 )
	{
		if( strstr( D_or_M, "Div" ) )
			insert_at_last( headR, tailR, 0 ); // Quotient is 0

		else
		{
			Dlist *temp = *head1;
			while( temp )
			{
				insert_at_last( headR, tailR, temp -> data ); // Reminder is divident
				temp = temp -> next;
			}
		}

		return SUCCESS;
	}

	// Repeated subtraction
	Dlist *qH = NULL, *qT = NULL;

	while( ( large = Find_largest( *head1, *head2 ) ) == LARGE_1 )
	{
		// Clear the current results to avoid wrong results
		*headR = NULL;
		*tailR = NULL;
		
		if( subtraction( head1, tail1, head2, tail2, headR, tailR ) == FAILURE )
			return FAILURE;

		// a = a - b, so Update the divident to new reduced value
		*head1 = *headR;
		*tail1 = *tailR;

		if( increment_list( &qH, &qT ) == FAILURE ) 
			return FAILURE;
	}

	// If both numbers are equal after last subtraction, increment quotient by 1
	if( large == EQUAL )
	{
		if( increment_list( &qH, &qT ) == FAILURE ) 
			return FAILURE;

		*head1 = *tail1 = NULL;
    	insert_at_last( head1, tail1, 0 );
	}
	
	// Prepare the result list based on Div or Mod
	*headR = NULL;
	*tailR = NULL;

	if( strstr( D_or_M, "Div" ) )
	{
		// Convert the quotient to result list
		if( qH == NULL )
			insert_at_last( headR, tailR, 0 );
		else
		{
			Dlist *temp = qH;
			while( temp )
			{
				insert_at_first( headR, tailR, temp -> data );
				temp = temp -> next;
			}
		}
	}
	
	else if( strstr( D_or_M, "Mod" ) )
	{
		// Copy remaining divident digits to result as reminder
		if( (*head1) -> data == 0 && !(*head1) -> next )
			insert_at_last( headR, tailR, 0 );
		else
		{
			Dlist *temp = *head1;
			while( temp )
			{
				insert_at_last( headR, tailR, temp -> data );
				temp = temp -> next;
			}
		}
	}
	
	free_list( &qH, &qT);

	// Remove leading zeroes from result
	while( (*headR)->next && (*headR)->data == 0 )
        delete_at_first( headR, tailR );

	return SUCCESS;
}

Status increment_list( Dlist **head, Dlist **tail )
{
    if( head == NULL || tail == NULL )
		return FAILURE;
    
	if( *head == NULL )
	{
        if( insert_at_first( head, tail, 1 ) != SUCCESS )
			return FAILURE;
        
		return SUCCESS;
    }

    Dlist *t = *tail;
    int carry = 1;
    while( t && carry )
	{
        int sum = t -> data + carry;
        t -> data = sum % 10;
        carry = sum / 10;
        t = t -> prev;
    }
    if( carry )
	{
        if( insert_at_first( head, tail, carry ) != SUCCESS )
			return FAILURE;
    }
	
    return SUCCESS;
}