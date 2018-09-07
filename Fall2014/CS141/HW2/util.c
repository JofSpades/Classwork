



/**
* function:  abs_diff(x,y)
*
* returns |x-y|
*/
double abs_diff(double x, double y) {

	int z = x - y;

	if(z < 0){
		z *= -1;
	}

	return z;

}

/**
* function:  median3(a,b,c)
*
* returns median ("middle value") among a, b and c.
*/
int median3(int a, int b, int c){

	if (((b < a) && (a < c)) || ((c < a) && (a < b))){
		return a;
	} else if (((a < b) && (b < c)) || ((c < b) && (b < a))){
		return b;
	} else if (((b < c) && (c < a)) || ((a < c) && (c < b))){
		return c;
	}

}

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
*/
unsigned  int sqrt_floor(unsigned int n) {

    int val = 0;

    for(int i = 0; i < n; i++){

    	if(i * i == n){

    		val = i;
    		break;

    	} else if (i * i >= n){

    		val = i - 1;
    		break;

    	}
    
    }

    return val;
 
}

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
int num_ones(unsigned int n) {

	int test = 0;
    int val = 0;
    int amnt = 0;

    for(int i = 1; i <= n; i = i * 2){

    	amnt++;

    }

    for(int i = amnt; i >= 0; i--){

    	test = n >> i;

    	if(test & 1){

    		val++;

    	}

    }

    return val;

}

