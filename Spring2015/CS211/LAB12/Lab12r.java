/** Complete the linked list code for 
  *
  *  show()    - traverse the list printing out the value in each node
  *  insert()  - the values are to be inserted in increasing order
  *  remove()  - remove the node from the list with the first occurrence of parameter value
  * 
  *  The C version of insert() and show() are contained in the file linked.c on the Notes page.
  *  The C version of remove() was to be written as part of Lab Exercise 6
  */

public class Lab12r
{
  private static boolean debug;
  
  public static void main (String[] args)
  {
    debug = false;
    if (args.length > 0 && args[0].equals("-d"))
      debug = true;
    
    System.out.println ("fact(5) is: " + fact(5) );
    System.out.println ("fact(15) is: " + fact(15) );
    
    debug = false;
    System.out.println ("fib(5) is: " + fib(5) );
    System.out.println ("fib(15) is: " + fib(15) );
    debug = true;
    
    System.out.println ("power(2, 5) is: " + power(2, 5) );
    System.out.println ("power(2, 15) is: " + power(2, 15) );
  }
  
 public static int fact (int num)
 {
   if (debug == true)
     System.out.println ("In fact(" + num + ")");
   
   if ( num <= 0 )
     return 1;
   else
     return num * fact(num - 1);
 }
 
 public static int fib (int num)
 {
   if (debug == true)
     System.out.println ("In fib(" + num + ")");
   
   if ( num <= 0 )
     return 0;
   else if ( num == 1 )
     return 1;
   else
     return fib(num - 2) + fib(num - 1);
 }
    
 public static boolean isPrime (int num)
 {
   if ( num <= 2 )
     return false;
   else if ( factorInRange( 2, num ) == false)
     return true;
   else
     return false;
 }
 
 public static boolean factorInRange (int m, int n)
 {
   if (debug == true)
     System.out.println ("In factorInRange(" + m + ", " + n + ")");
   
   
   if ( m >= n )
     return false;
   else if ( n%m == 0)
     return true;
   else if ( m == 2)
     return factorInRange (m+1, n);
   else
     return factorInRange (m+2, n);
 }
 
 public static int power (int base, int exp)
 {
   if (debug == true)
     System.out.println ("In power(" + base + ", " + exp + ")");
   
   if ( exp <= 0 )
     return 1;
   else if ( exp == 1)
     return base;
   else if (exp % 2 == 0)
   {
     int tmp = power (base, exp/2);
     return ( tmp * tmp );
   }
   else
     return base * power (base, exp-1);
 }   
    
 public static int greatestCommonDivisor (int a, int b)
  {
   if (debug == true)
     System.out.println ("In gcd(" + a + ", " + b + ")");
   
    // computer Greatest Common Divisor recursively via Euclid's algorithm
    if (b == 0)
      return a;
    else 
      return greatestCommonDivisor (b, a%b);
  }
}
  
  
