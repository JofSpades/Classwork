import java.io.*;
import java.util.*;

public class ScannerFileIntReader
{

 public static void main (String[] args)
 {
   File f = new File ("MazeData4.txt");
   Scanner sc = null;
   
   try
   {
     sc = new Scanner (f);
   }
   catch (FileNotFoundException fnfe)
   {
     System.out.println ("File did not exist");
     return;
   }
   
   int count = 0;
   
   // loop until all integers are read from the file
   while (sc.hasNextInt())
   {
     int val = sc.nextInt();
     count++;
   }
   System.out.println (count + " values were read in.");
   
   System.out.println ("Goodbye");
 }
     
}