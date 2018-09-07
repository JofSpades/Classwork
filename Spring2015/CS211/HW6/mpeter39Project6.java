import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
//Uses GD2 to build the GUI desplay of the game
public class mpeter39Project6{
	public static void main(String[] args) {
		//default delay
		int delay = 250;
		//check the given commandline arguments for proper
		if(args.length > 3){
			System.out.println("TOO MANY ARGUMENTS PLEASE TRY AGAIN\nLOOKING FOR <filename> -d <time in ms> or <filename>");
			System.exit(-1);
		}
		if(args.length == 2){
			if(args[0].equals("-d")){
				//setting the new delay if provided
				delay = Integer.parseInt(args[1]);
			} else {
				System.out.println("WRONG FLAG OR IN WRONG ORDER LOOKING FOR <-d> <delay in ms>");
			}
		} else if (args.length == 1){
			System.out.println("MISSING INFORMATION LOOKING FOR <-d> <delay in ms>");
			System.exit(-1);
		}
		//setup of new grid
		int i, j, k;
		int x = 0;
		int y = 0;
		int found;
		Random rand = new Random();
		int[][] ants = new int[100][2];
		int[][] doodlebug = new int[5][2];
		Creature[][] gen = new Creature[22][22];
		Creature[][] genPlus = new Creature[22][22];
		GridDisplay disp = new GridDisplay(30, 22);
		char[][] keyMap = {{'E', 'X', 'P', 'L', 'I', 'N', 'A', 'T', 'I', 'O', 'N', 'S', ':', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
						   {'X', '=', 'W', 'A', 'L', 'L', ';', 'T', 'H', 'E', ' ', 'D', 'O', 'O', 'D', 'L', 'E', 'B', 'U', 'G', 'S', ' '},
						   {'W', 'I', 'L', 'L', ' ', 'G', 'E', 'T', ' ', 'D', 'A', 'R', 'K', 'E', 'R', ' ', 'I', 'N', ' ', 'R', 'E', 'D'},
						   {'C', 'O', 'L', 'O', 'R', ' ', 'A', 'S', ' ', 'I', 'T', ' ', 'G', 'E', 'T', 'S', ' ', ' ', ' ', ' ', ' ', ' '},
						   {'C', 'L', 'O', 'S', 'E', 'R', ' ', 'T', 'O', ' ', 'D', 'E', 'A', 'T', 'H', ';', ' ', ' ', ' ', ' ', ' ', ' '},
						   {'A', 'N', 'T', 'S', ' ', 'A', 'R', 'E', ' ', 'T', 'H', 'E', ' ', 'G', 'R', 'E', 'E', 'N', ' ', ' ', ' ', ' '},
						   {'S', 'P', 'O', 'T', 'S', ';', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
		for(i = 0; i < 22; i++){
			for(j = 0; j < 7; j++){
				disp.setChar(j, i, keyMap[j][i]);
			}
		}
		for(i = 0; i < 22; i++){
			disp.setChar(8,i,'X');
			disp.setChar(29,i,'X');
			disp.setChar(i + 8,0,'X');
			disp.setChar(i + 8,21,'X');
		}
		for(i = 0; i < 100; i++){
			do{ 
				found = 0;
				x = rand.nextInt(20) + 9;
				y = rand.nextInt(20) + 1;
				for(j = 0; j < 100; j++){
					if(ants[j][0] == x && ants[j][1] == y){
						found = 1;
					}
				}
			}while(found == 1);
			if(found != 1){
				ants[i][0] = x;
				ants[i][1] = y;
			}
		}
		for(i = 0; i < 5; i++){
			do{ 
				found = 0;
				x = rand.nextInt(20) + 9;
				y = rand.nextInt(20) + 1;
				for(j = 0; j < 5; j++){
					if(doodlebug[j][0] == x && doodlebug[j][1] == y){
						found = 1;
					}
				}
				for(j = 0; j < 100; j++){
					if(ants[j][0] == x && ants[j][1] == y){
						found = 1;
					}
				}
			}while(found == 1);
			if(found != 1){
				doodlebug[i][0] = x;
				doodlebug[i][1] = y;
			}
		}
		for(i = 0; i < 100; i++){
			Ant newAnt = new Ant(ants[i][0] - 9, ants[i][1] - 1);
			disp.setColor(ants[i][0], ants[i][1], newAnt.getColor());
			gen[ants[i][0] - 9][ants[i][1] - 1] = newAnt;
			genPlus[ants[i][0] - 9][ants[i][1] - 1] = newAnt;
		}
		for(i = 0; i < 5; i++){
			DoodleBug newDoodlebug = new DoodleBug(doodlebug[i][0] - 9, doodlebug[i][1] - 1);
			disp.setColor(doodlebug[i][0], doodlebug[i][1], newDoodlebug.getColor());
			gen[doodlebug[i][0] - 9][doodlebug[i][1] - 1] = newDoodlebug;
			genPlus[doodlebug[i][0] - 9][doodlebug[i][1] - 1] = newDoodlebug;
		}
		GridDisplay.mySleep(delay);
		while(true){
			for(i = 0; i < 20; i++){
				for(j = 0; j < 20; j++){
					if(gen[i][j] != null){
						if(gen[i][j].getClass() == DoodleBug.class){
							gen[i][j].move(gen,genPlus);
							//gen[i][j].spawn(gen);
							if(gen[i][j].getColor() == Color.BLACK){
								genPlus[i][j] = null;
							}
						} else if(gen[i][j].getClass() == Ant.class){
							gen[i][j].move(gen,genPlus);
							//gen[i][j].spawn(gen);
						}
					}
				}
			}
			copyover(genPlus,disp);
			disp.mySleep(delay);
		}
	}
	// public static void update(Creature[][] gen, Creature[][] genPlus){
	// 	int i, j, x, y;
	// 	for(i = 1; i <= 20; i++){
	// 		for(j = 1; j <= 20; j++){
	// 			if(gen[i][j] != null){
	// 				x = gen[i][j].getX();
	// 				y = gen[i][j].getY();
	// 				genPlus[x][y] = gen[i][j];
	// 				gen[x][y] = genPlus[i][j];
	// 			}
	// 		}
	// 	}
	// }
	public static void copyover(Creature[][] gen, GridDisplay disp){
		int i, j;
		for(i = 0; i < 20; i++){
			for(j = 0; j < 20; j++){
				if(gen[i][j] != null){
					disp.setColor(i + 9, j + 1, gen[i][j].getColor());
				} else {
					disp.setColor(i + 9, j + 1, Color.WHITE);
				}
			}
		}
	}
}
