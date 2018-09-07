



/**
* function:  abs_diff(x,y)
*
* returns |x-y|
*/
double abs_diff(double x, double y);

/**
* function:  median3(a,b,c)
*
* returns median ("middle value") among a, b and c.
*/
int median3(int a, int b, int c);

/**
* function:  sqrt_floor(n)
*
* returns the "largest integer less than or equal to sqrt(n)"
*
* Examples:
*
*       n       value-returned
*
*       5            2
*       4            2
*       10           3
*       40           6
*       44           6
*
* Note:  your implementation must be self-contained -- i.e., you can't
*        call any library functions (like the math library's sqrt function!).
*
*/
unsigned  int sqrt_floor(unsigned int n);

/**
* function:  num_ones(n)
*
* returns the number of 1s in the binary representation of n.
*
* Examples:
*
*     The binary representation of 5 is 101; so num_ones(5) would report 2
*
*     num_ones(32) would report 1
*
*     num_ones(15) is 4    (binary representation:  1111)
*
*  Notes:  n is unsigned so
*
*/
int num_ones(unsigned int n);

