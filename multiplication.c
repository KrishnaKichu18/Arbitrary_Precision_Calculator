/*******************************************************************************************************************************************************************
 * Function Name    : multiplication
 * Description      : Performs multiplication of two large positive numbers represented as doubly linked lists. Each node stores
 *                    a single digit, where the head represents the Most Significant Digit (MSD) and the tail represents the Least
 *                    Significant Digit (LSD). The function implements the classical digit-by-digit multiplication algorithm
 *                    (similar to manual long multiplication), where each digit of one number is multiplied with every digit of
 *                    the other number. Partial results are accumulated directly in the result list with proper carry propagation.
 *
 * Prototype        : Status multiplication( Dlist **head1, Dlist **tail1,
 *                                           Dlist **head2, Dlist **tail2,
 *                                           Dlist **headR, Dlist **tailR );
 *
 * Input Parameters : head1, tail1 -> Pointers to the head and tail of the first number list.
 *                    head2, tail2 -> Pointers to the head and tail of the second number list.
 *                    headR, tailR -> Pointers to the head and tail of the result number list (initially empty).
 *
 * Return Value     : SUCCESS -> If multiplication completes successfully.
 *                    FAILURE -> If memory allocation fails during node creation.
 *
 * Special Cases    :
 *                    • If either operand is zero → Result = 0.
 *                    • Sign handling is not performed here; it is managed externally by the main driver.
 *
 * Algorithm        :
 *                    1. Determine the lengths of both operand lists (len1 and len2).
 *                    2. Initialize the result list with (len1 + len2) zeros — the maximum possible number of digits.
 *                    3. Starting from the LSD of the second number:
 *                         a. Multiply the current digit of the second number with all digits of the first number (LSD → MSD).
 *                         b. Add product + existing result digit + carry.
 *                         c. Update result digit as (product % 10) and propagate carry.
 *                    4. After processing one digit of the second number, shift the result starting position left by one node.
 *                    5. Remove any leading zeros from the final result.
 *
 * Notes            :
 *                    • Performs in-place accumulation, avoiding creation of temporary intermediate lists.
 *                    • Time Complexity: O(n × m), where n and m are the lengths of the two input numbers.
 *                    • This function operates purely on magnitudes; external logic handles sign and display formatting.
 *******************************************************************************************************************************************************************/

#include "apc.h"

Status multiplication( Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR )
{
	
	// Find length of both numbers
	int len1 = 0,
		len2 = 0;

	for( Dlist *t = *tail1; t; t = t -> prev ) len1++;
	for( Dlist *t = *tail2; t; t = t -> prev ) len2++;

	// Create result list initialised with zeroes and maximum possible digits will be sum of both lengths
	for( int i = 0; i < len1 + len2; i++ )
		insert_at_first( headR, tailR, 0 );

	Dlist *temp2 = *tail2;
	Dlist *tempR_start = *tailR;

	while( temp2 )
	{
		int carry = 0;
		Dlist *temp1 = *tail1;
		Dlist *tempR = tempR_start;

		while( temp1 )
		{
			// Product will be updated with carry and existing value at result node
			int product = ( temp1 -> data * temp2 -> data ) + tempR -> data + carry;

			tempR -> data = product % 10;
			carry = product / 10;

			// Traverse both lists to next nodes ( towards MSB ) 
			temp1 = temp1 -> prev;
			tempR = tempR -> prev;

		}

		// If carry is remaining, add it to the next result node before next multiplication
		if( carry )
			tempR -> data += carry;

		// Move to next digit of second number and adjust starting position in result list
		temp2 = temp2 -> prev;
		tempR_start = tempR_start -> prev;
	}

	// Remove leading zeroes from result
	while( (*headR)->next && (*headR)->data == 0 )
        delete_at_first( headR, tailR );
		
	return SUCCESS;
}