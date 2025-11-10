/*******************************************************************************************************************************************************************
 * Function Name    : addition
 * Description      : Performs addition of two large positive numbers represented as doubly linked lists. Each node stores a 
 *                    single digit, where the head represents the Most Significant Digit (MSD) and the tail represents the 
 *                    Least Significant Digit (LSD). The function adds digits from right to left (LSD to MSD), manages carry 
 *                    propagation, and constructs the result in a separate doubly linked list.
 *
 * Prototype        : Status addition( Dlist **head1, Dlist **tail1,
 *                                     Dlist **head2, Dlist **tail2,
 *                                     Dlist **headR, Dlist **tailR );
 *
 * Input Parameters : head1, tail1 -> Pointers to the head and tail of the first number list.
 *                    head2, tail2 -> Pointers to the head and tail of the second number list.
 *                    headR, tailR -> Pointers to the head and tail of the result number list (initially empty).
 *
 * Return Value     : SUCCESS -> If addition is performed successfully.
 *                    FAILURE -> If memory allocation fails during node insertion.
 *
 * Algorithm        :
 *                    1. Initialize carry = 0.
 *                    2. Traverse both lists from the tail (LSD) towards the head (MSD).
 *                    3. Add corresponding digits and the carry (if any).
 *                    4. Insert the resulting digit at the head of the result list.
 *                    5. Continue until all digits and any remaining carry are processed.
 *                    6. Remove any leading zeros from the result list.
 *
 * Notes            :
 *                    • This function assumes both input lists represent non-negative magnitudes.
 *                    • Sign management is handled externally in main().
 *******************************************************************************************************************************************************************/

#include "apc.h"

Status addition( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR )
{

	int carry = 0;
	Dlist *digits_1 = *tail1;
	Dlist *digits_2 = *tail2;

	while( digits_1 || digits_2 || carry )
	{
		int sum = carry;

		// Add the digits from both numbers if available
		if( digits_1 )
		{
			sum += digits_1 -> data ;
			digits_1 = digits_1 -> prev;
		}

		if( digits_2 )
		{
			sum += digits_2 -> data;
			digits_2 = digits_2 -> prev;
		}

		int digit = sum % 10; // The single digit to be added to the list
		carry = sum / 10;     // Will be 1 for sum > 9

		if( insert_at_first( headR, tailR, digit ) != SUCCESS )
			return FAILURE;

	}

	// Remove leading zeroes from result
	while( (*headR)->next && (*headR)->data == 0 )
        delete_at_first( headR, tailR );

	return SUCCESS;
}