/*******************************************************************************************************************************************************************
 * Function Name    : subtraction
 * Description      : Performs subtraction of two large positive numbers stored in doubly linked lists. The digits are stored
 *                    such that the head represents the Most Significant Digit (MSB) and the tail represents the Least Significant Digit (LSB).
 *                    This function assumes that the caller (typically main) has already determined which number is larger and handled any
 *                    sign management or operand swapping before the call.
 *
 * Prototype        : Status subtraction( Dlist **head1, Dlist **tail1,
 *                                       Dlist **head2, Dlist **tail2,
 *                                       Dlist **headR, Dlist **tailR );
 *
 * Input Parameters : head1, tail1 -> Pointers to the head and tail of the first (larger) number list.
 *                    head2, tail2 -> Pointers to the head and tail of the second (smaller) number list.
 *                    headR, tailR -> Pointers to the head and tail of the result number list (initially empty).
 *
 * Return Value     : SUCCESS -> If subtraction is carried out successfully.
 *                    FAILURE -> If memory allocation fails during node insertion.
 *
 * Special Cases    :
 *                    • If both numbers are equal → Result is 0.
 *                    • Leading zeros in the result are automatically removed.
 *
 * Algorithm        :
 *                    1. Compare both numbers to detect equality.
 *                    2. If equal, result = 0.
 *                    3. Otherwise, traverse from the tail (LSB) of both lists and subtract digit-by-digit.
 *                    4. Handle borrow propagation whenever a digit underflows.
 *                    5. Insert each difference digit at the head of the result list.
 *                    6. Remove any leading zeros from the final result.
 *
 * Notes            :
 *                    • This function does not handle sign determination; that logic must be done by the caller.
 *                    • If required, uses Swap_lists() externally before calling subtraction().
 *******************************************************************************************************************************************************************/

#include "apc.h"


Status subtraction( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR )
{

	// Compare and find the larger number
	Status larger = Find_largest( *head1, *head2 );
	int	diff = 0,
		borrow = 0;

	// Numbers are equal, so result will be zero
	if( larger == EQUAL )
	{
		insert_at_first( headR, tailR, 0 );
		return SUCCESS;
	}

	// Subtraction Logic
	Dlist *digits_1 = *tail1;
	Dlist *digits_2 = *tail2;

	while( digits_1 || digits_2 )
	{
		// Get each digits to subtract
		int d1 = 0;
		if ( digits_1 )
		{
			d1 = digits_1 -> data;
			digits_1 = digits_1 -> prev;
		}

		int d2 = 0;
		if ( digits_2 )
		{
			d2 = digits_2 -> data;
			digits_2 = digits_2 -> prev;
		}

		// Subtract the borrow from previous calculation
		d1 -= borrow;

		// Update Borrow based on digits value
		if( d1 < d2)
		{
			borrow = 1; 
			d1 += 10;
		}
		else
			borrow = 0;

		// Calculate the difference	
		diff = d1 - d2;

		if( insert_at_first( headR, tailR, diff ) == FAILURE )
			return FAILURE;

	}

	// Remove leading zeroes from result
	while( (*headR)->next && (*headR)->data == 0 )
        delete_at_first( headR, tailR );

	return SUCCESS;
}

// Swap two lists for magnitude comparison
void Swap_lists( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2 )
{
	Dlist *tempH = *head1, *tempT = *tail1;

	*head1 = *head2;
	*tail1 = *tail2;
	
	*head2 = tempH;
	*tail2 = tempT;

}