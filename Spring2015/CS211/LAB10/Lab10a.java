public class Lab10a
{
  
  public static void main (String[] args)
  {
    // create an instance of the MyStack2 class
    MyStack2 s1 = new MyStack2();
    
    // push 4 points onto the stack
    Point2d pt1 = new Point2d (15, 25);
    s1.push (pt1);
    pt1 = new Point2d (35, 45);
    s1.push (pt1);
    pt1 = new Point2d (55, 65);
    s1.push (pt1);
    pt1 = new Point2d (75, 85);
    s1.push (pt1);
    
    // while the stack is not empty, print out the top Point and pop the stack
    while (!s1.isEmpty())
    {
      Point2d pt2 = s1.top();
      System.out.println ("Point: " + pt2 );
      s1.pop();
    }
  }
}


