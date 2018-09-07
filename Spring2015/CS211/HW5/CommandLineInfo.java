import java.io.*;
import java.util.*;

public class CommandLineInfo
{

 public static void main (String[] args)
 {
   System.out.println ("This program was given " + args.length + " command line arguments");
   
   for (int i = 0; i < args.length ; i++)
   {
     System.out.println ("Arg[" + i + "] is: " + args[i]);
   }
   
   System.out.println ("Goodbye");
 }
     
}