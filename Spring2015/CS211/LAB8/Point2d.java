import java.io.*;

/** A Java Class to represent a point in a 2D grid 
  * 
  *   @author  Pat Troy
  */

class Point2d
{
 // The X and Y coordinates of the point
  int x;
 protected int y;

 // A trick to help with debugging
 private boolean debug;

 public void dprint (String s)
   {
    // print the debugging string only if the "debug"
    // data member is true
    if (debug)
       System.out.println("Debug: " + s);
   }

 public void setDebug (boolean b)
   {
    debug = b;
   }

 public Point2d (int px, int py)
   {
    x = px;
    y = py;

    // turn off debugging
    debug = false;
   }

 public Point2d ()
   {
    this (0, 0);
   }

 public Point2d (Point2d pt)
   {
    x = pt.getX();
    y = pt.getY();

    // a better method would be to replace the above code with
    //    this (pt.getX(), pt.getY());
    // especially since the above code does not initialize the
    // variable debug.  This way we are reusing code that is already
    // working.
   }

 public void setX(int px)
   {
    dprint ("setX(): Changing value of X from " + x + " to " + px );
    x = px;
   }

 public int getX()
   {
    return x;
   }

 public void setY(int py)
   {
    dprint ("setY(): Changing value of Y from " + y + " to " + py );
    y = py;
   }

 public int getY()
   {
    return y;
   }

 public void setXY(int px, int py)
   {
    setX(px);
    setY(py);
   }

 public double distanceFrom (Point2d pt)
   {
    int dx = Math.abs(x - pt.getX());
    int dy = Math.abs(y - pt.getY());

    // check out the use of dprint()
    dprint ("distanceFrom(): deltaX = " + dx);
    dprint ("distanceFrom(): deltaY = " + dy);

    return Math.sqrt((dx * dx) + (dy * dy));
   }

 public double distanceFromOrigin ()
   {
    return distanceFrom (new Point2d ( ));
   }

 public String toStringForXY()
   {
    String str = "(" + x + ", " + y;
    return str;
   }

 public String toString()
   {
    String str = toStringForXY() + ")";
    return str;
   }


 public static void main (String[] args)
   {
    Point2d  pt1 = new Point2d ();

    // Code to test Access Modifiers: Lab 8, Questions 3
    // pt1.x = 1;               // LINE 119
    // pt1.y = 2;               // LINE 120
    // pt1.debug = true;        // LINE 121
    
    System.out.println ("pt1 = " + pt1);

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

   }
}
