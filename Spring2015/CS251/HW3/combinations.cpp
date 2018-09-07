/* combinations.cpp
 *    Given n elements, take k.
 *
 * From http://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture25.html
 
 Running program gives:
 
 1 2 3
 1 2 4
 1 2 5
 1 3 4
 1 3 5
 1 4 5
 2 3 4
 2 3 5
 2 4 5
 3 4 5
 
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

void combinations (int v[], int start, int n, int k, int maxk) {
    int     i;
    
    /* k here counts through positions in the maxk-element v.
     * if k > maxk, then the v is complete and we can use it.
     */
    if (k > maxk) {
        /* insert code here to use combinations as you please */
        for (i=1; i<=maxk; i++) printf ("%i ", v[i]);
        printf ("\n");
        return;
    }
    
    /* for this k'th element of the v, try all start..n
     * elements in that position
     */
    for (i=start; i<=n; i++) {
        
        v[k] = i;
        
        /* recursively generate combinations of integers
         * from i+1..n
         */
        combinations (v, i+1, n, k+1, maxk);
    }
}

int main (int argc, char *argv[]) {
    int     v[100], n, k;
    
    n=10;   // For this example values run from 1..5
    k=4;   // Take 3 at a time
    
    /*
    if (argc != 3) {
        printf ("Usage: %s n k\n", argv[0]);
        exit (1);
    }
    n = atoi (argv[1]);
    k = atoi (argv[2]);
    */
    
    /* generate all combinations of n elements taken
     * k at a time, starting with combinations containing 1
     * in the first position.
     */
    combinations (v, 1, n, 1, k);
    exit (0);
}