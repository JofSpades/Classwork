/** Complete the linked list code for 
  *
  *  show()    - traverse the list printing out the value in each node
  *  insert()  - the values are to be inserted in increasing order
  *  remove()  - remove the node from the list with the first occurrence of parameter value
  * 
  *  The C version of insert() and show() are contained in the file linked.c on the Notes page.
  *  The C version of remove() was to be written as part of Lab Exercise 6
  */

public class Lab12
{
  public static void main (String[] args)
  {
    MyList list1 = new MyList();
    MyList list2 = new MyList();
    
    // insert some values
    list1.insert (5);
    list1.insert (18);
    list1.insert (10);
    list1.show();
    list1.insert (3);
    list1.show();
    
    list2.insert (51);
    list2.insert (68);
    list2.insert (24);
    list2.show();
    list2.insert (93);
    list2.show();
    
    // remove some values
    list1.remove (10);
    list1.show();
    list1.remove (7);
    list1.show();
    list1.remove (3);
    list1.show();
    list1.remove (18);
    list1.show();
    
    list2.remove (93);
    list2.remove (24);
    list2.remove (51);
    list2.show();
    list2.remove (68);
    list2.show();
    list2.remove (3);
    list2.show();
    list2.remove (18);
    list2.show();
  }
}
  
  
class MyList
{
  private MyLNode head;
  
  public MyList()
  {
    head = null;
  }
   
  public void show()
  {
    MyLNode tmp = head;
    while(tmp == null){
      System.out.println(tmp.elem);
      tmp = tmp.next;
    }
  }
  
  public void insert (int v1)
  {
    MyLNode tmp = new MyLNode (v1);
    if(head == null){
      head = tmp;
    } else {
      MyLNode traverse = head;
      while(traverse != null){
        if(traverse.next != null){
          if(tmp.elem > traverse.elem){
            tmp.next = traverse.next;
            traverse.next = tmp;
            return;
          }
        } else {
          traverse.next = tmp;
          return;
        }
        traverse = traverse.next;
      }
    }
  }
  
  public void remove (int v1)
  {
    
  }
  

}


class MyLNode
{
  int elem;
  MyLNode next;
  
  MyLNode (int v1)
  {
    elem = v1;
    next = null;
  }
}