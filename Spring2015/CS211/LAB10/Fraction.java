/** Fraction Class  - represent a rational number as a fraction using an integer numerator and denominator 
  * 
  *  instance variables
  *     num - the integer numerator part of the fraction
  *     den - the integer denominator part of the fraction
  * 
  * Restrictions on the class
  * - the denominator should never be a value of 0
  * - the denominator should never be negative 
  * - the fraction should be reduced to its lowest terms
  */

public class Fraction
{
  private int num;
  private int den;
  
  // Default Constructor: set the fraction to 0/1
  public Fraction()
  {
    num = 0;
    den = 1;
    normalize();
    reduce();
  }
  
  // Single integer Constructor: set the fraction to val/1
  public Fraction (int val)
  {
    num = val;
    den = 1;
    normalize();
    reduce();
  }
  
  // Double integer Constructor: set the fraction to val1/val2
  //   if val2 is negative, normalize (invert sign on both val1 and val2)
  //   reduce the fraction to its lowest terms
  public Fraction (int val1, int val2)
  {
    num = val1;
    den = val2;
    normalize();
    reduce();
  }
  
  
  public Fraction add (Fraction f2)
  {
    int tempNum1 = this.num;
    int tempNum2 = f2.num;
    int tempDen1 = this.den;
    int tempDen2 = f2.den;

    Fraction result = new Fraction (((tempNum1 * tempDen2) + (tempNum2 * tempDen1)), (tempDen1 * tempDen2));
    
    return result;
  }
  
  
  public boolean equals (Fraction f2)
  { // true if num1*den2 == num2*den1
    if ( num*f2.den == f2.num*den )
      return true;
    else
      return false;
  }
  
  public String toString()
  { // used with System.out.print() methods
    return num + "/" + den;
  }
  
  private void normalize ()
  {
    if ( den < 0 )
    {
      num = -num;
      den = -den;
    }
  }
  
  private void reduce ()
  {
    int a = num;
    int b = den;
    
    // take the absolute value of both a and b (make sure a and b are postive numbers)
    if (a < 0)
      a = -a;
    if (b < 0)
      b = -b;
    
    int gcd = greatestCommonDivisor (a, b);
    
    num = num / gcd;
    den = den /gcd;
  }
  
  private static int greatestCommonDivisor (int a, int b)
  {
    // computer Greatest Common Divisor recursively via Euclid's algorithm
    if (b == 0)
      return a;
    else 
      return greatestCommonDivisor (b, a%b);
  }
  
  public static void main (String[] args)
  {
    Fraction f1, f2, f3;
    f1 = new Fraction (-42, -56);
    System.out.println ("f1: " + f1);
    f2 = new Fraction (52, -13);
    System.out.println ("f2: " + f2);
    
    f3 = f1.add(f2);
    System.out.println ("f3: " + f3);
    System.out.println ("f1 must not be changed as a result of calling add(): " + f1);
    System.out.println ("f2 must not be changed as a result of calling add(): " + f2);
    
    // uncomment for Q4 (delete above comment line)
    f1 = new Fraction ();
    f2 = new Fraction (0);
    System.out.println ("\nEquality Testing Part 1\nf1: " + f1 + ", f2: " + f2 );
    if ( f1 == f2 )
      System.out.println (" f1 == f2 ");
    else
      System.out.println (" f1 != f2 ");
    
    if ( f1.equals(f2) == true )
      System.out.println (" f1 equals f2 ");
    else
      System.out.println (" f1 does not equal f2 ");
      
    f2 = f1;
    System.out.println ("\nEquality Testing Part 2\nf1: " + f1 + ", f2: " + f2 );
    if ( f1 == f2 )
      System.out.println (" f1 == f2 ");
    else
      System.out.println (" f1 != f2 ");
    
    if ( f1.equals(f2) == true )
      System.out.println (" f1 equals f2 ");
    else
      System.out.println (" f1 does not equal f2 ");
    // end of comment block (delete below comment line)
  }
  
}