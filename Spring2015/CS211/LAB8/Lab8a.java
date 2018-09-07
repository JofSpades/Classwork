public class Lab8a
{
  public static void main (String[] args)
   {
    System.out.println ("Working with the Point2d class\n");
    
    Point2d  pt1 = new Point2d ();   // LINE 7
    
    // Code to test Access Modifiers: Lab 8, Questions 1 and 4
    // pt1.x = 1;               // LINE 10 
    // pt1.y = 2;               // LINE 11
    // pt1.debug = true;        // LINE 12

    System.out.println ("pt1 = " + pt1);   // LINE 14

    Point2d pt2 = new Point2d(4, 3);

    System.out.println ("pt2 = " + pt2);

    pt1.setDebug(true);  // turning on debugging
    // statements for pt1

    System.out.println ("Distance from " + pt1 + " to " + pt2 +
   " is " + pt1.distanceFrom(pt2));

    System.out.println ("Distance from " + pt2 + " to " + pt1 +
   " is " + pt2.distanceFrom(pt1));

    System.out.println ("Distance from " + pt1 + " to the origin (0, 0) is " +
   pt1.distanceFromOrigin());

    System.out.println ("Distance from " + pt2 + " to the origin (0, 0) is " +
   pt2.distanceFromOrigin());

    pt1.setXY(3, 5);
    System.out.println ("pt1 = " + pt1);

    pt2.setXY(-3, -5);
    System.out.println ("pt2 = " + pt2);

    System.out.println ("Distance from " + pt1 + " to " + pt2 +
   " is " + pt1.distanceFrom(pt2));

    System.out.println ("Distance from " + pt2 + " to " + pt1 +
   " is " + pt2.distanceFrom(pt1));

    pt1.setDebug(false);    // turning off debugging 
       // statements for pt1

    System.out.println ("Distance from " + pt1 + " to the origin (0, 0) is " +
   pt1.distanceFromOrigin());

    System.out.println ("Distance from " + pt2 + " to the origin (0, 0) is " +
   pt2.distanceFromOrigin());

    /////////////////////////////////////////////////////////
    // Working with the Point3d class
    /////////////////////////////////////////////////////////
    System.out.println ("\nWorking with the Point3d class\n");
    
    Point3d pt3 = new Point3d ();
    System.out.println ("pt3 = " + pt3);

    Point3d pt4 = new Point3d (1,2,3);
    System.out.println ("pt4 = " + pt4);

    pt3.setDebug(true);  // turn on debugging statements
    // for pt3
    System.out.println ("Distance from " + pt4 + " to " + pt3 +
   " is " + pt4.distanceFrom(pt3));

    System.out.println ("Distance from " + pt3 + " to the origin (0, 0) is " +
   pt3.distanceFromOrigin());

    System.out.println ("Distance from " + pt4 + " to the origin (0, 0) is " +
   pt4.distanceFromOrigin());

    pt3.setXYZ(3, 5, 7);
    System.out.println ("pt3 = " + pt3);

    pt4.setXYZ(-3, -5, -7);
    System.out.println ("pt4 = " + pt4);

    System.out.println ("Distance from " + pt3 + " to " + pt4 +
   " is " + pt3.distanceFrom(pt4));

    System.out.println ("Distance from " + pt4 + " to " + pt3 +
   " is " + pt4.distanceFrom(pt3));

    pt3.setDebug(false);    // turning off debugging 
       // statements for pt3

    System.out.println ("Distance from " + pt3 + " to the origin (0, 0) is " +
   pt3.distanceFromOrigin());

    System.out.println ("Distance from " + pt4 + " to the origin (0, 0) is " +
   pt4.distanceFromOrigin());


   }
}