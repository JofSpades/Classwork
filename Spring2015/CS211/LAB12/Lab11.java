public class Lab11
{
  public static void doStuff(Animal a)
  { 
    System.out.println ("\nIn doStuff with a " + a.getType() );
    a.move();  // LINE 6
    a.speak(); // LINE 7
  }
  
 public static void main (String[] args) 
  {
    Animal a = new Animal("Animal");
    doStuff (a);   // LINE 13
    
    Dog d = new Dog("Dog");
    doStuff(d);    // LINE 16
    
    Bird b = new Bird("Bird");
    doStuff(b);    // LINE 19
    
    a = d;
    doStuff (a);   // LINE 22

    a = b;
    doStuff (a);   // LINE 25
  }
}


// Animal class - note should be in its own file of Animal.java
class Animal
{
  private String type;
  
  public Animal (String t)
  {
    type = t;
  }
  
  public String getType()
  {
    return type;
  }
  
  public void move()
  {
    System.out.println ("I am moving.");
  }
  
  public void speak()
  {
    System.out.println ("I am speaking.");
  }
}


// Dog class - note should be in its own file of Dog.java
class Dog extends Animal
{
  public Dog (String t)
  {
    super(t);               // LINE 62
  }
  
  @Override public void move()
  {
    System.out.println ("I am running.");
  }
  
  @Override public void speak()
  {
    System.out.println ("Woof. Woof.");
  }
}


// Bird class - note should be in its own file of Bird.java
// 
//  Note that the code used here contains a mistake.
//    adding in the @Override keyword quickly resolves the mistake in the code.
class Bird extends Animal
{
  public Bird (String t)
  {
    super(t);
  }
  
  @Override public void move()
  {
    System.out.println ("I am flying.");
  }
  
  @Override public void speaks()
  {
    System.out.println ("Caw. Caw.");
  }
}