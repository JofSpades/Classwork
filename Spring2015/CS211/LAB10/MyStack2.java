public class MyStack2
{
  private MyNode2 head;
  
  public void MyStack2()
  {
    head = null;
  }
  
  public boolean isEmpty()
  {
    if (head == null)
      return true;
    else
      return false;
  }
  
  public void push (Point2d pt)
  {
    MyNode2 tmp = new MyNode2 (pt);
    tmp.next = head;
    head = tmp;
  }
  
  public void pop()
  {
    head = head.next;
  }
  
  public Point2d top()
  {
    return head.coord;
  }
  
  public static void main (String[] args)
  {
    MyStack s1 = new MyStack();
    s1.push (1, 2);
    s1.push (10, 20);
    s1.push (30, 40);
    s1.push (50, 60);
    s1.push (70, 80);
    
    while (!s1.isEmpty())
    {
      System.out.println ("x: " + s1.topX() + ", y: " + s1.topY());
      s1.pop();
    }
  }
}

class MyNode2
{
  MyNode2 next;
  Point2d coord;
  
  MyNode2 (Point2d pt)
  {
    coord = pt;
    next = null;
  }
}