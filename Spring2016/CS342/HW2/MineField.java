import java.io.*;
import java.util.*;

public class MineField
{
	private int[][] mineField;
	private int minesLeft;

	//Used to get data at any point
	public int getValue( int x, int y )
	{
		return this.mineField[x][y];
	}
	
	public void setRemainingMines( int newAmount )
	{
		this.minesLeft = newAmount;
	}
	
	public int totalRemainingMines(  )
	{
		return this.minesLeft;
	}
	
	private int[][] mineFieldSetup(  )
	{
		int[][] returnArray = new int[12][12];
		int[] xArray = new int[10];
		int[] yArray = new int[10];
		int[] xCheck = new int[10];
		int[] yCheck = new int[10];
		int arrayPosition = 0;
		int[] values = new int[9];
		int count = 0;
		int amount = 0;

		for ( int i = 0; i < 10; i++ )
		{
			xArray[i] = ( int ) ( Math.random(  ) * 10 );
			yArray[i] = ( int ) ( Math.random(  ) * 10 );
		}
		
		for ( int i = 0; i < 10; i++ )
		{
			xCheck[xArray[i]]++;
			yCheck[yArray[i]]++;
			if ( xCheck[xArray[i]] == 2 && yCheck[yArray[i]] == 2 )
			{
				xArray[i] = ( int ) ( Math.random(  ) * 10 );
				yArray[i] = ( int ) ( Math.random(  ) * 10 );
				i = -1;
			}
		}
		
		for ( int i = 0; i < 12; i++ )
		{
			for ( int j = 0; j < 12; j++ )
			{
				returnArray[i][j] = 0;
			}
		}
		
		for ( int i = 0; i < 10; i++ )
		{
			returnArray[xArray[i] + 1][yArray[i] + 1] = -1;
		}
		
		for ( int i = 1; i < 11; i++ )
		{
			for ( int j = 1; j < 11; j++ )
			{
				if ( returnArray[i][j] != -1 )
				{
					for ( int k = ( i - 1 ); k <= ( i + 1 ); k++ )
					{
						for ( int l = ( j - 1 ); l <= ( j + 1 ); l++ )
						{
							if ( returnArray[k][l] == -1 )
							{
								returnArray[i][j] += 1;
							}
						}
					}
				}
			}
		}
		return returnArray;
	}

	public void print(  )
	{
		System.out.println( "+---+---+---+---+---+---+---+---+---+---+" );
		for ( int i = 1; i < 11; i++ )
		{
			for ( int j = 1; j < 11; j++ )
			{
				if ( this.mineField[i][j] == -1 )
				{
					System.out.print( "|" + this.mineField[i][j] + " " );
				}
				else
				{
					System.out.print( "| " + this.mineField[i][j] + " " );
				}
			}
			System.out.print( "|\n" );
			System.out.println( "+---+---+---+---+---+---+---+---+---+---+" );
		}
	}

	public MineField(  )
	{
		this.minesLeft = 10;
		this.mineField = this.mineFieldSetup(  );
	}
}
