
// file:  arr_util.h

/**
* returns 1 if array a[0..n-1] is sorted in ascending order (technically, 
*   non-descending order).
* Returns 0 otherwise
*/
int is_sorted(int a[], int n);

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
void histogram(unsigned int data[], int n);

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
int num_distinct(int a[], int n);


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
int same_contents(int a[], int b[], int n);

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
void rotate_right(int a[], int n);



