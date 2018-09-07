#include <stdio.h>

int main (int argc, char** argv)
{
 int i;
 int count;
 int total;
 int val;
 double average;

 /* prompt the user for input */
 printf ("Enter in a list of numbers followed by the terminal value of -999\n");
 
 /* loop until the user enters -999 */
 scanf ("%d", &val);
 while (val != -999)
   {
    total = total + val;
    count++;
    scanf("%d", &val);
   }

 /* calculate the average of the values read in */
 average = total / count;

 /* display the results */
 printf ("For the list of %d numbers with a total of %d\n", count, total);
 printf ("   the average is: %15.5f\n", average);

 return 0;
} 
