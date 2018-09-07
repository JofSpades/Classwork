import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
//Uses GD2 to build the GUI desplay of the game
public class mpeter39Project5{
	public static void main(String[] args) {
		//check for just filename
		if(args.length > 2){
			System.out.println("TOO MANY ARGUMENTS PLEASE TRY AGAIN\nLOOKING <filename> ONLY");
			System.exit(-1);
		} else if(args.length == 0){
			System.out.println("TOO FEW ARGUMENTS PLEASE TRY AGAIN\nLOOKING <filename> ONLY");
			System.exit(-1);
		}
		File readIn = new File(args[0]);
		Scanner scanVal = null;
		try
		{
			scanVal = new Scanner (readIn);
		}
		catch (FileNotFoundException fnfe)
		{
			System.out.println ("File did not exist");
			System.exit(-1);
		}
		int size = 500;
		int[] val = new int[size];
		int index = -1;
		int valcount = 0;
		// loop until all integers are read from the file
		while (scanVal.hasNextInt()){			
			index++;
			if(index == size -1){
				//reallocating
				int[] temp = new int[index * 2];
				System.arraycopy(val, 0, temp, 0, size);
				size *= 2;
				val = temp;
			}
			val[index] = scanVal.nextInt();
			valcount++;
		}
		int check;
		index = 0;
		int xpos = 0;
		int ypos = 0;
		int xbound = 0;
		int ybound = 0;
		while(index < valcount){
			xpos = val[index];
			ypos = val[index + 1];
			//getting starting value
			if(xpos > 0 && ypos > 0){
				xbound = xpos;
				ybound = ypos;
				break;
			}
			//errors checking for the bounds of the board
			if(xpos == 0) {
				System.err.println("X END CANNOT BE 0");
			}
			if(ypos == 0) {
				System.err.println("Y END CANNOT BE 0");
			}
			index += 2;
		}
		index += 2;
		//setup of new grid
		int[][] gen = new int[xbound + 2][ybound + 2];
		int[][] genPlus = new int[xbound + 2][ybound + 2];
		GridDisplay disp = new GridDisplay(xbound + 2, ybound + 2);
		initlizeDisplay(disp, xbound, ybound);
		while(index < valcount){
			xpos = val[index];
			ypos = val[index + 1];
			//getting the living spots
			if((xpos >= 1 && ypos >= 1) && (xpos <= xbound && ypos <= ybound)){
				gen[xpos][ypos] = 1;
				index += 2;
				continue;
			}
			//error checking for the living dots
			if(xpos < 1) {
				System.err.println("X POSITION CANNOT BE LESS THAN 1");
			}
			if(ypos < 1) {
				System.err.println("Y POSITION CANNOT BE LESS THAN 1");
			}
			if(xpos > xbound) {
				System.err.println("X POSITION CANNOT BE OUTSIDE THE BOUNDS");
			}
			if(ypos > ybound) {
				System.err.println("Y POSITION CANNOT BE OUTSIDE THE BOUNDS");
			}
			index += 2;
		}
		setDisplay(disp, gen, gen, xbound, ybound);
		GridDisplay.mySleep(250);
		/*
		the standard pattern I will be using is as follows, ? refers to the cell in question

		1. x| |    2.  |x|    3.  | |x   4.  | |    5.  | |    6.  | |    7.  | |    8.  | | 
		   -----      -----      -----      -----      -----      -----      -----      -----
		    |?|        |?|        |?|        |?|x       |?|        |?|        |?|       x|?| 
		   -----      -----      -----      -----      -----      -----      -----      -----
		    | |        | |        | |        | |        | |x       |x|       x| |        | | 

		*/
		int change;
		int i, j, k;
		int[][] location = {{-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};
		while(true){
			for(i = 1; i <= xbound; i++){
				for(j = 1; j <= ybound; j++){
					//checking for the amount of chages made for the nearby live squares
					change = 0;
					//top left corner
					if(i == 1 && j == 1){
						if(gen[xbound][2] == 1){
							change++;
						}
						if(gen[xbound][1] == 1){
							change++;
						}
						if(gen[xbound][ybound] == 1){
							change++;
						}
						if(gen[1][ybound] == 1){
							change++;
						}
						if(gen[2][ybound] == 1){
							change++;
						}
						for(k = 3; k <= 5; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
					//top side
					} else if(j == 1){
						if(gen[i - 1][ybound] == 1){
							change++;
						}
						if(gen[i][ybound] == 1){
							change++;
						}
						if(gen[i + 1][ybound] == 1){
							change++;
						}
						for(k = 3; k <= 7; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
					//top right corner
					} else if(i == xbound && j == 1){
						if(gen[i - 1][ybound] == 1){
							change++;
						}
						if(gen[xbound][ybound] == 1){
							change++;
						}
						if(gen[1][ybound] == 1){
							change++;
						}
						if(gen[1][1] == 1){
							change++;
						}
						if(gen[1][2] == 1){
							change++;
						}
						for(k = 5; k <= 7; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
					//right side
					} else if(i == xbound){
						for(k = 0; k <= 1; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
						if(gen[1][j - 1] == 1){
							change++;
						}
						if(gen[1][j] == 1){
							change++;
						}
						if(gen[1][j + 1] == 1){
							change++;
						}
						for(k = 5; k <= 7; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
					//bottom right corner
					} else if(i == xbound && j == ybound){
						for(k = 0; k <= 1; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
						if(gen[1][ybound - 1] == 1){
							change++;
						}
						if(gen[1][ybound] == 1){
							change++;
						}
						if(gen[1][1] == 1){
							change++;
						}
						if(gen[xbound][1] == 1){
							change++;
						}
						if(gen[xbound - 1][1] == 1){
							change++;
						}
						if(gen[xbound - 1][ybound] == 1){
							change++;
						}
					//bottom side
					} else if(j == ybound){
						for(k = 0; k <= 3; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
						if(gen[i + 1][1] == 1){
							change++;
						}
						if(gen[i][1] == 1){
							change++;
						}
						if(gen[i - 1][1] == 1){
							change++;
						}
						if(gen[i + location[7][0]][j + location[7][1]] == 1){
							change++;
						}
					// bottom left corner
					} else if(i == 1 && j == ybound){
						if(gen[xbound][ybound - 1] == 1){
							change++;
						}
						for(k = 1; k <= 3; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
						if(gen[2][1] == 1){
							change++;
						}
						if(gen[1][1] == 1){
							change++;
						}
						if(gen[xbound][1] == 1){
							change++;
						}
						if(gen[xbound][ybound] == 1){
							change++;
						}
					//left side
					} else if(i == 1){
						if(gen[xbound][j - 1] == 1){
							change++;
						}
						for(k = 1; k <= 5; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
						if(gen[xbound][j + 1] == 1){
							change++;
						}
						if(gen[xbound][j] == 1){
							change++;
						}
					//everything else	
					} else {
						for(k = 0; k <= 7; k++){
							if(gen[i + location[k][0]][j + location[k][1]] == 1){
								change++;
							}
						}
					}//end look around the ith and jth positoin
					if(change < 2 || change > 3){
						genPlus[i][j] = 0;
					} else if(change == 3){
						genPlus[i][j] = 1;
					}//end checks for what to change
				}//end for(j)
			}//end for(i)
			setDisplay(disp, genPlus, gen, xbound, ybound);
			GridDisplay.mySleep(250);
		}//end while(true)
	}
	public static void initlizeDisplay (GridDisplay disp, int xbound, int ybound){
		int i, j;
		for(i = 0; i <= xbound + 1; i++){
			for(j = 0; j <= ybound + 1; j++){
				if((i == 0) || (j == 0) || (i == (xbound + 1)) || (j == (ybound + 1))){
					disp.setChar(i, j, 'X');
				} else {
					disp.setColor(i,j, Color.BLACK);
				}
			}
		}
	}
	//this is used to completely overwrite the old generation with the new one.
	public static void setDisplay (GridDisplay disp, int[][] genPlus, int[][] gen, int xbound, int ybound){
		int i;
		int j;
		for(i = 1; i <= xbound; i++){
			for(j = 1; j <= ybound; j++){
				if( genPlus[i][j] == 1){
					disp.setColor(i, j, Color.GREEN);
				} else {
					disp.setColor(i, j, Color.BLACK);
				}
				gen[i][j] = genPlus[i][j];
			}
		}
	}
}
