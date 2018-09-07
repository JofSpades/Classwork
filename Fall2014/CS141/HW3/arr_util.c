#include <stdio.h>

// file:  arr_util.c

/**
* returns 1 if array a[0..n-1] is sorted in ascending order (technically, 
*   non-descending order).
* Returns 0 otherwise
*/
int is_sorted(int a[], int n){

	/*
		The for loop runs through the array for any case where the next value is smaler than the
		current value and if that is found count is incremented for each time it comes across.
	*/

	int count = 0;

	for(int i = 0; i < n; i++){

		if(a[i + 1] < a[i]){

			return 0;

		}

	}

	// If the program makes it this far it returns a value of 1

	return 1;

}

/**
* displays an ASCII histogram as in HW2, but the number of data points
*   is n rather than 4.
*
* Assumptions/Details:  
*
*     Each column/bar is labeled with an appropriate capital letter
*        starting from 'A' and continuing left-to-right.
*
*    
*     A histogram is drawn only if n <= 26 -- i.e., only labels 
*	'A'...'Z' are possible.
*     If n is greater than 26, the function should print an error
*       message and return.
*
*     REMEMBER:  characters also have integer interpretations and
*         in ASCII, the integer values for 'A'...'Z' are contiguous
*	  and in increasing order.
*/
void histogram(unsigned int data[], int n){

	//Starting with a check for size

	if (n > 26){

		printf("Too many values try less than 26.");

	} else {

		/*check for maximum value*/

		int maximum = 0;

		for(int a = 0; a < n; a++){

			if(maximum < data[a]){

				maximum = data[a];

			}

		}

		/*graph drawing with one row at a time */

		int track = maximum;

		printf("\n\n");

		for(int a = 0; a < maximum; a++){

			for(int b = 0; b < n; b++){

				if(data[b] >= track){

					printf(" X");

				} else {

					printf("  ");

				}

			}
		
			printf(" ");

			printf("\n");

			track--;

		}

		/*bottom formatting*/

		for(int a = 0; a < n; a++){

			printf("--");

		}

		printf("-\n");

		for(int a = 0; a < n; a++){

			printf(" %c", 65 + a);

		}

		printf("\n");

	}

}

/**
* returns the number of distinct values stored in array a.
*
* parameters:
*
*     a:  array of data
*     n:  length of array a
*
* Examples:
*
*    if a = {1, 2, 3}, all three entries are distinct so 3 is returned.
*
*    if a = {1, 1, 1, 1, 1}, then only one distinct value (1) so 1 is 
*          returned.
*
* Rules:  you may NOT rearrange the array in any way; you may not invoke
*   any external functions; you may not use any additional arrays.
*
*/
int num_distinct(int a[], int n){

	int count = 0;

	for(int i = 0; i < n; i++){

		for(int j = 0; j < n; j++){

			if((a[i] != a[j]) && (j != i)){

				count++;

				if(count >= n){

					return count;
		
				}

			}

		}

		

	}

	if(count == 0){

		count++;
		
	}

	return count;

}


/**
* returns 1 if a[0..n-1] and b[0..n-1] have the same contents; 
*    returns 0 otherwiwse.
*
* a[] and b[] "have the same contents" when:
*
*      - every integer in a[] is also in b[]
*      - every integer in b[] is also in a[]
*      - all such common values appear exactly the same
*           number of times in both a[] and b[]
*
* examples:
* 
*    a = {1, 2, 3}, b = {2, 3, 4}    NO
*    a = {1, 2, 3}; b = {2, 3, 1}    YES
*    a = {1, 2, 2}; b = {2, 2, 1}    YES
*    a = {1, 2, 2}; b = {2, 1, 1}    NO
*    a = {1, 1, 2, 2, 2}; b = {2, 1, 2, 1, 2}    YES
*    
* RULES:  You may NOT re-order the elements of the arrays.
*/
int same_contents(int a[], int b[], int n){

	int maximum = 0;

	for(int i = 0; i < n; i++){

		if(maximum < a[i]){

			maximum = a[i];

		}

	}

	int c[maximum];

	for(int i = 0; i < maximum; i++){

		c[i] = 0;

	}

	for(int i = 0; i < n; i++){

		c[a[i]]++;

	}

	for(int i = 0; i < n; i++){

		if(c[b[i]] > 0){

			c[b[i]]--;

		}

	}

	for(int i = 0; i < maximum; i++){

		if(c[i] > 0){

			return 0;

		}

	}

	return 1;

}

/**
* rotates contents of array one position to the right.
*
* element in last position (index n-1) moves to first position (idx 0).
*
* Examples:
*     
*    {1, 2, 3, 4} rearranged to become {4, 1, 2, 3}
*
*    {1, 2, 1, 2} rearranged to become {2, 1, 2, 1}
*
* NOTES:
*  
*    Modifies given array; does not create a second array
*/
void rotate_right(int a[], int n){

	int temp = 0;
	int ender = a[n - 1];
	int b[n];

	for(int i = 0; i < n; i++){

		b[i + 1] = a[i];

	}

	b[0] = ender;

	for(int i = 0; i < n; i++){

		a[i] = b[i];

	}

}