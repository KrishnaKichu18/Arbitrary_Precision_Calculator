/*******************************************************************************************************************************************************************
 * Title        : Krishna_M_M_APC_Arbitrary_Precision_Calculator_25017E_031
 * Project      : APC - Arbitrary Precision Calculator
 * Developer    : Krishna M
 * Date         : 31/10/2025
 *
 * Description  : Main driver program for the Arbitrary Precision Calculator. This module validates command-line arguments,
 *                converts numeric strings into doubly linked lists, determines operation type and operand signs, and then
 *                calls the corresponding arithmetic function. The program supports addition, subtraction, multiplication,
 *                division, modulus, and power for numbers of arbitrary length.
 *
 *                Each number is represented as a doubly linked list where:
 *                - The head node stores the Most Significant Digit (MSD)
 *                - The tail node stores the Least Significant Digit (LSD)
 *
 *                The program performs sign management, magnitude comparison, and formatted result display for all operations.
 *                Arithmetic operations are implemented in modular source files with clear separation of concerns.
 *
 * Supported Operations:
 *                +  → Addition
 *                -  → Subtraction
 *                x  → Multiplication
 *                /  → Division (Quotient)
 *                %  → Modulus (Remainder)
 *                ^  → Power (Exponentiation)
 *
 * Features:
 *                • Handles arbitrarily large integers beyond built-in data type limits.
 *                • Maintains correct sign and magnitude for all operations.
 *                • Detects and handles divide-by-zero safely.
 *                • Supports zero and negative exponents (integer logic: negative powers → 0).
 *                • Provides formatted, right-aligned output for clarity.
 *                • Demonstrates modular, structured, and memory-safe design using doubly linked lists.
 *
 * Key Concepts Demonstrated:
 *                - Dynamic memory allocation and linked list manipulation.
 *                - Modular arithmetic algorithm implementation.
 *                - Robust sign handling and operand normalization.
 *                - Command-line parsing and input validation.
 *                - Clean formatted output generation.
 *
 * Usage Example:
 *                ./apc.out <number1> <operator> <number2>
 *                Example → ./apc.out -1234 x +56
 *
 * Output Format:
 *                    -1234
 *                x     +56
 *                ---------
 *                =  -69104
 *******************************************************************************************************************************************************************/

#include "apc.h"
#include <stdlib.h>
#include <stdio.h>

int main( int argc, char* argv[] )
{
	/* Validate CLArguments */
	if( Validate_arguments( argc, argv ) == FAILURE )
	{
		printf("INFO : Invalid Arguments! Please provide Two Numbers and One Operator.\n");
		printf("Format : ./a.out <number1> <operator> <number2>\n");
		exit(1);
	}

	/* Declare the pointers */
	Dlist *head1 = NULL, 
		  *tail1 = NULL,
		  *head2 = NULL,
		  *tail2 = NULL,
		  *headR = NULL,
		  *tailR = NULL;
	char operator;

	/* Convert both Numbers to LLs */
	String_to_list( &head1, &tail1, argv[1] );
	String_to_list( &head2, &tail2, argv[3] );
	operator = argv[2][0];

	char sign1 = '+', sign2 = '+';
	if( argv[1][0] == '+' ) sign1 = '+';
	if( argv[1][0] == '-' ) sign1 = '-';

	if( argv[3][0] == '+' ) sign2 = '+';
	if( argv[3][0] == '-' ) sign2 = '-';

	char final_sign;

	switch ( operator )
	{
		case '+':
			/* call the function to perform the addition operation */

			if( sign1 ==  sign2 )
			{
				addition( &head1, &tail1, &head2, &tail2, &headR, &tailR );
				final_sign = sign1;
			}

			else if( sign1 == '-' )
			{
				// (-a) + (b)

				Status larger = Find_largest( head1, head2 );
				if( larger == LARGE_2 )
				{
					Swap_lists( &head1, &tail1, &head2, &tail2 );
					final_sign = '+';  // b is larger means, result positive
				}
				else
				{
					final_sign = '-'; // a is larger means, result negative
				}

				subtraction( &head1, &tail1, &head2, &tail2, &headR, &tailR );
			}

			else if( sign2 == '-' )
			{
				// (a) + (-b)

				Status larger = Find_largest( head1, head2 );
				if( larger == LARGE_2 )
				{
					Swap_lists( &head1, &tail1, &head2, &tail2 );
					final_sign = '-'; // b is larger means, result negative
				}
				else
				{
					final_sign = '+'; // a is larger means, result positive
				}

				subtraction( &head1, &tail1, &head2, &tail2, &headR, &tailR );
			}
			
			break;

		case '-':	
			/* call the function to perform the subtraction operation */

			if( sign1 != sign2 )
			{
				addition( &head1, &tail1, &head2, &tail2, &headR, &tailR );
				final_sign = sign1;
			}

			else 
			{
				// Same sign: do maginitude based subtraction
				Status larger = Find_largest( head1, head2 );
				if( larger == LARGE_2 )
				{
					Swap_lists( &head1, &tail1, &head2, &tail2 );
					final_sign = ( sign1 == '+' ) ? '-': '+'; // Result sign is opposite
				}
				else
				{
					final_sign = sign1; // Result sign is same as bigger number
				}

				subtraction( &head1, &tail1, &head2, &tail2, &headR, &tailR );

			}

			break;

		case 'x':	
			/* call the function to perform the multiplication operation */

			multiplication( &head1, &tail1,&head2, &tail2, &headR, &tailR );

			if( sign1 == sign2 )
				final_sign = '+';
			else
				final_sign = '-';

			break;

		case '/':	
			/* call the function to perform the division operation */

			division( &head1, &tail1,&head2, &tail2, &headR, &tailR, "Div" );

			if( sign1 == sign2 )
				final_sign = '+';
			else
				final_sign = '-';

			break;

		case '%':	
			/* call the function to perform the division operation */

			division( &head1, &tail1,&head2, &tail2, &headR, &tailR, "Mod" );

			if( sign1 == sign2 )
				final_sign = '+';
			else
				final_sign = '-';

			break;

		case '^': 
			/// Check for negative exponent (if sign2 == '-')
			if( sign2 == '-' )
			{
				// Result of any base^(-exp) = 0 (integer APC logic)
				headR = tailR = NULL;
				insert_at_first( &headR, &tailR, 0 );
				final_sign = '+';
				break;
			}

			// Determine sign of result
			if( sign1 == '+' )
				final_sign = '+';

			else
			{
				// sign1 is '-', exponent positive → depends on even/odd
				if( is_exp_even( head2 ) == EVEN )
					final_sign = '+';

				else
					final_sign = '-';
			}

			// Perform power normally, exponent is positive
			power( &head1, &tail1, &head2, &tail2, &headR, &tailR );

			break;

		default:
			printf("INFO : Invalid Input:-( Try again...)\n");
			return FAILURE;
	}

	
	print_calculation( argv[1], operator, argv[3], headR, &final_sign );
	return 0;
}