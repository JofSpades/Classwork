public class Lab10b
{
  
  public static void main (String[] args)
  {
    // Create an instance of the MyStack2 class
    MyStack2 s1 = new MyStack2();
    
    // Perform 4 push operations
    Point2d pt1 = new Point2d (15, 25);
    s1.push (pt1);
    pt1.setXY (35, 45);
    s1.push (pt1);
    pt1.setXY (55, 65);
    s1.push (pt1);
    pt1.setXY (75, 85);
    s1.push (pt1);
    
    // While the stack is not empty, print the top point and pop the stack
    while (!s1.isEmpty())
    {
      Point2d pt2 = s1.top();
      System.out.println ("Point: " + pt2 );
      s1.pop();
    }
  }
}


