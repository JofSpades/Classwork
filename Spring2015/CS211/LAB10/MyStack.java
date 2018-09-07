public class MyStack
{
  private MyNode head;
  
  public MyStack()
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
  
  public void push (int v1, int v2)
  {
    MyNode tmp = new MyNode (v1, v2);
    tmp.next = head;
    head = tmp;
  }
  
  public void pop()
  {
    head = head.next;
  }
  
  public int topX()
  {
    return head.x;
  }
  
  public int topY()
  {
    return head.y;
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


class MyNode
{
  int x, y;
  MyNode next;
  
  MyNode (int v1, int v2)
  {
    x = v1;
    y = v2;
    next = null;
  }
}