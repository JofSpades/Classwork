import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GD2
{
    public static void main( String args[] )
   {
      // create the grid of 25 rows and 35 columns
      GridDisplay disp = new GridDisplay(25, 35);
      
      // some code to demonstrate the use of the setChar and setColor methods of GridDisplay
      disp.setChar(0,0,'t');
      disp.setColor(0,0,Color.BLUE);
      disp.setChar(1,1,'x');
      for (int i = 1; i < 10; i = i + 2)
        disp.setChar (i, i*2, 'v');
      for (int i = 2; i < 12; i = i + 2)
        disp.setColor (i+1, i, Color.RED);
      for (int i = 3; i < 12; i++)
      {
        disp.setColor (1, i, Color.GREEN);
        GridDisplay.mySleep (250);  // sleep for 250 milliseconds i.e. 1/4 second
      }
      for (int i = 11; i > 3; i--)
      {
        disp.setColor (1, i, Color.LIGHT_GRAY);
        GridDisplay.mySleep (500);  // sleep for 500 milliseconds i.e. 1/2 second
      }
      for (int i = 2; i < 12; i++)
      {
        disp.setColor (i, 3, Color.GREEN);
        GridDisplay.mySleep (100);  // sleep for 100 milliseconds i.e. 1/10 second
      }
      
      for (int j = 0 ; j < 10 ; j ++)
      {
        for (int i = 2; i < 12; i++)
          disp.setColor (15, i, Color.RED);
        GridDisplay.mySleep (250);  // sleep for 250 milliseconds i.e. 1/4 second
        
        for (int i = 2; i < 12; i++)
          disp.setColor (15, i, Color.MAGENTA);
        GridDisplay.mySleep (250);  // sleep for 250 milliseconds i.e. 1/4 second
      }
   } 
    

}  // end of GD2 class

class GridDisplay extends JFrame
{
   private JLabel labels[];

   private Container container;
   private GridLayout grid1;
   int rowCount;
   int colCount;

   // set up GUI
   public GridDisplay(int rows, int cols)
   {
      super( "Doodlebugs and Ants" );
      setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

      // set up grid layout struture of the display
      rowCount = rows;
      colCount = cols;
      grid1 = new GridLayout( rows, cols );
      container = getContentPane();
      container.setLayout( grid1 );

      // create and add buttons
      labels = new JLabel[ rows * cols ];

      for ( int count = 0; count < labels.length; count++ ) {
         labels[ count ] = new JLabel( " " );
         labels[count].setOpaque(true);
         container.add( labels[ count ] );
      }

      // set up the size of the window and show it
      setSize( cols * 15 , rows * 15 );
      setVisible( true );

   } // end constructor GridLayoutDemo

   // display the given char in the (row,col) position of the display
   public void setChar (int row, int col, char c)
   {
     if ((row >= 0 && row < rowCount) && (col >= 0 && col < colCount) )
     {
       int pos = row * colCount + col;
       labels [pos].setText("" + c);  
     }
   }
   
   // display the given color in the (row,col) position of the display
   public void setColor (int row, int col, Color c)
   {
     if ((row >= 0 && row < rowCount) && (col >= 0 && col < colCount) )
     {
       int pos = row * colCount + col;
       labels [pos].setBackground(c);  
     }
   }
   
    // puts the current thread to sleep for some number of milliseconds to allow for "animation"
    public static void mySleep( int milliseconds)
    {
      try
      {
        Thread.sleep(milliseconds);
      }
      catch (InterruptedException ie)
      {
      }
    }
} // end class GridDisplay
