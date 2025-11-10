/*******************************************************************************************************************************************************************
 * Function Name    : power
 * Description      : Computes the power of a large number (base^exponent) using repeated multiplication. Both the base and 
 *                    exponent are represented as doubly linked lists where each node stores a single digit — the head node 
 *                    represents the Most Significant Digit (MSD) and the tail node represents the Least Significant Digit (LSD). 
 *                    The result is initialized to 1 and multiplied repeatedly by the base until the exponent becomes zero.
 *
 * Prototype        : Status power( Dlist **baseH, Dlist **baseT,
 *                                  Dlist **expH,  Dlist **expT,
 *                                  Dlist **headR, Dlist **tailR );
 *
 * Input Parameters : baseH, baseT -> Pointers to the head and tail of the base number list.
 *                    expH,  expT  -> Pointers to the head and tail of the exponent number list.
 *                    headR, tailR -> Pointers to the head and tail of the result number list (initially empty).
 *
 * Return Value     : SUCCESS -> If power computation completes successfully.
 *                    FAILURE -> If multiplication or node insertion fails due to memory allocation error.
 *
 * Special Cases    :
 *                    • If exponent = 0 → Result = 1 (by mathematical definition).
 *                    • If base = 0 and exponent = 0 → Result = 1 (consistent with most programming conventions).
 *                    • Handles very large base and exponent values that exceed standard data types.
 *
 * Sign Handling (Managed Externally):
 *                    • Negative exponent → Result = 0 (integer APC logic).
 *                    • Negative base:
 *                          - If exponent is even → Result sign = '+'.
 *                          - If exponent is odd  → Result sign = '-'.
 *                    • Positive base → Result sign = '+'.
 *
 * Algorithm        :
 *                    1. Initialize result = 1.
 *                    2. If exponent = 0 → return result as 1.
 *                    3. While exponent > 0:
 *                         a. Copy current result into a temporary list.
 *                         b. Clear the original result list.
 *                         c. Multiply temporary list with the base list.
 *                         d. Decrement exponent by one using subtract_one().
 *                    4. Remove any leading zeros from the result list.
 *
 * Notes            :
 *                    • Implements repeated multiplication (O(exponent × base_length)) — suitable for moderate exponents.
 *                    • Exponentiation-by-squaring can replace this method for optimization (future enhancement).
 *                    • Works purely on magnitudes; sign and display are handled externally by the main driver.
 *******************************************************************************************************************************************************************
 * Helper Functions :
 *                    1. subtract_one() → Decrements a number (in Dlist form) by one, managing borrow propagation.
 *                    2. copy_list()    → Creates a duplicate of a given doubly linked list (digit-by-digit copy).
 *                    3. free_list()    → Frees all nodes in a given doubly linked list and resets head and tail to NULL.
 *******************************************************************************************************************************************************************/

#include "apc.h"


Status power ( Dlist **baseH, Dlist **baseT, Dlist **expH, Dlist **expT, Dlist **headR, Dlist **tailR )
{
    *headR = NULL;
    *tailR = NULL;
    
    // Initialise result as 1
    insert_at_first( headR, tailR, 1 );

    // Case: Exponent is zero
    if( (*expH) -> data == 0 && (*expH) -> next == NULL )
        return SUCCESS;         // Already result is initialised with 1

    // Run loop until exponent reaches zero
    while( (*expH) -> data || (*expH) -> next )
    {
        // Res_Copy is copy of the result that will be multiplied with the base
        Dlist* Res_copyH = NULL, *Res_copyT = NULL;
        copy_list( *headR, *tailR, &Res_copyH, &Res_copyT );

        // Free the result list inorder to
        free_list( headR, tailR );

        // Product = Product * base
        if( multiplication( &Res_copyH, &Res_copyT, baseH, baseT, headR, tailR ) == FAILURE )
            return FAILURE;

        // Exponent--
        subtract_one( expH, expT );

    }

    // Remove leading zeroes from result
	while( (*headR) -> next && (*headR) -> data == 0 )
        delete_at_first( headR, tailR );

    return SUCCESS;

}


void subtract_one( Dlist **head, Dlist **tail )
{
    Dlist *temp = *tail;

    while ( temp )
    {
        if (temp -> data > 0)
        {
            temp -> data -= 1;
            break;
        }
        else
        {
            temp -> data = 9;
            temp = temp -> prev;
        }
    }

    // Remove leading zeroes from result
	while( (*head) -> next && (*head) -> data == 0 )
        delete_at_first( head, tail );
        
}


void copy_list( Dlist *srcH, Dlist *srcT, Dlist **dstH, Dlist **dstT )
{
    *dstH = *dstT = NULL;

    while ( srcH )
    {
        insert_at_last( dstH, dstT, srcH -> data );
        srcH = srcH -> next;
    }
}

void free_list( Dlist **head, Dlist **tail )
{
    if( head == NULL || *head == NULL ) 
        return;
    
    Dlist *cur = *head, *next;

    while( cur )
    {
        next = cur -> next;
        free( cur );
        cur = next;
    }

    *head = *tail = NULL;
}