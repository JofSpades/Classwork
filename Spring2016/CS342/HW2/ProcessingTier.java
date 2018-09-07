import java.io.*;
import java.util.*;

public class ProcessingTier
{
	private MineField field;
	private Score scoreData;

	//Constructor that sets up all the connections to the classes that are called upon
	public ProcessingTier(  )
	{
		this.field = new MineField(  );
		this.scoreData = new Score(  );
	}
	
	// check for the values stored to be a mine
	public boolean isMine( int x, int y )
	{
		//gets the values stored at the mine field location
		int value = this.field.getValue( x, y );

		//checks if mine returns accordingly
		if ( value == -1 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	// assumed to be called from a non mine spot
	public int minesNearby( int x, int y )
	{
		return this.field.getValue( x, y );
	}
	
	//return the total amount of mines 
	public int getMinesLeft(  )
	{
		return this.field.totalRemainingMines(  );
	}
	
	//gets the current score to display
	public int getScore(  )
	{
		return this.scoreData.getScore(  );
	}
	
	//returns the top ten scores
    public int[] getTopTen(){
        return this.scoreData.getTopScore();
	}
	
	//used to return the names for the top ten
    public String[] getTopNames(){
        return this.scoreData.getTopNames();
	}
	
	//updates the count of mines left to find
	public void foundMine(  )
	{
		this.field.setRemainingMines( this.field.totalRemainingMines(  ) - 1 );
	}
	
	//starts the game
	public void gameStart(  )
	{
		this.scoreData.gameStart(null  );
	}
	
	//ends the game
	public void gameEnd( boolean winner, String name )
	{
		//if the player is a winner then save the score
		if ( winner )
		{
			this.scoreData.didWin(  );
		}
		//else just clean up;
		this.scoreData.gameEnd( name );
	}
	
	//used to debug the mine locations
	private void printMineField(  )
	{
		this.field.print(  );
	}
	
	//mini debug function
	public static void main( String[]argv )
	{
		ProcessingTier test = new ProcessingTier(  );
		
		test.gameEnd(true, null);
		test.printMineField(  );
//		test.getTopNames();
		System.out.println(test.getTopTen());
		System.out.println( test.getMinesLeft(  ) );
	}
}
