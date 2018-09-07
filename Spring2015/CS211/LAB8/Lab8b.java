import java.io.*;


public class Lab8b
{

 public static void main (String[] args)
 {
  int val;

  System.out.println ("Inside main");

  LabExample inst1 = new LabExample();                     // LINE 1
  LabExample inst2 = new LabExample();
  inst1.setStorage (5);                        // LINE 2
  inst2.setStorage (1);                        // LINE 3
  
  System.out.println ("inst1 contains: " + inst1.getStorage() );  // LINE 4
  System.out.println ("inst2 contains: " + inst2.getStorage() );  
  inst1.modStorage();
  inst2.modStorage();                                              
  inst2.modStorage();
  System.out.println ("inst1 now contains: " + inst1.getStorage() );  
  System.out.println ("inst2 now contains: " + inst2.getStorage() );  // LINE 5
  
  System.out.println ("\nAbout to call funct1()");
  funct1();                                    // LINE 6

  System.out.println ("About to call funct2");
  val = funct2(8);                             // LINE 7
  System.out.println ("funct2 returned a value of " + val);
  
  LabExample.staticMethod();                   // LINE 8
 }

 public static void funct1 ()
 {
  System.out.println ("Inside funct1");
 }

 public static int funct2 (int param)
 {
  System.out.println ("Inside funct2 with param " + param);
  return param * 2;
 }
}

class LabExample
{
  private int storage;
  
  public void setStorage(int s)
  {
    storage = s;
  }
  
  public int getStorage ()
  {
    return storage;
  }
  
  public void modStorage()
  {
    storage = storage * 2;
  }
  
  public static void staticMethod ()
  {
    System.out.println ("Inside staticMethod() ");
  }
}
