import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
public class Creature{
	protected int daysLastBreed;
	protected int xpos;
	protected int ypos;
	protected int[][] location = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	protected Color creatureColor;
	protected Color myColor;
	//initlizing function
	public Creature(int x, int y){
		this.xpos = x;
		this.ypos = y;
		this.daysLastBreed = 0;
	}
	public int isEmptyAndValid(int x, int y, Creature[][] gen){
		if(x > 0 && y > 0 && x < 20 && y < 20){
			if(gen[x][y] == null){
				return 1;
			}
		}
		return 0;
	}
	//coments in the next two functinos were an attempt to increase the chances of moving and spawning
	public void move(Creature[][] gen, Creature[][] genPlus){
		int i;
		int check = 0;
		// int[] count = {0,1,2,3};
		int spot = (int) (Math.random() * 4);
		if(isEmptyAndValid((this.xpos + location[spot][0]), (this.ypos + location[spot][1]), gen) == 1){
			genPlus[this.xpos + location[spot][0]][this.ypos + location[spot][1]] = gen[xpos][ypos];
		}
		this.daysLastBreed++;
		// //moving in random direction
		// //this is so that there will always be movement
		// // while loop was used to run this check first and if the spot is valid 
		// while(isEmptyAndValid((this.xpos + location[spot][0]), (this.ypos + location[spot][1]), gen) == 1){
		// 	//check value re initlized to see how much of the directions
		// 	//havn't been tried
		// 	check = 0;
		// 	//marking what was found
		// 	for(i = 0; i < 4; i++){
		// 		if(spot == count[i]){
		// 			count[i] = -1;
		// 		}
		// 	}
		// 	//counting up how many open spot there are left to try
		// 	for(i = 0; i < 4; i++){
		// 		if(count[i] != -1){
		// 			check++;
		// 		}
		// 	}
		// 	//if there are no more open spots it ends the while loop
		// 	if(check == 0){
		// 		break;
		// 	}
		// 	//get next random spot to check
		// 	spot = this.rand.nextInt(4);
		// }
		// //applying the new direction
		// //if check is 0 then that means that there are no open directions to move
		// if(check == 0){
		// 	return;
		// } else if(check != 0){
		// 	genPlus[this.xpos + location[spot][0]][this.ypos + location[spot][1]] = gen[xpos][ypos]; 
		// }
	}
	public int spawn(Creature[][] gen, int spawnDay){
		int i, check = 1;
		int[] count = {0,1,2,3};
		int spot =  (int) (Math.random() * 4);
		// //spawning in random direction
		// //this is so that there will always be movement
		// // while loop was used to run this check first and if the spot is valid 
		// while(isEmptyAndValid((xpos + location[spot][0]), (ypos + location[spot][1]), gen) == 1){
		// 	//check value re initlized to see how much of the directions
		// 	//havn't been tried
		// 	check = 0;
		// 	//marking what was found
		// 	for(i = 0; i < 4; i++){
		// 		if(spot == count[i]){
		// 			count[i] = -1;
		// 		}
		// 	}
		// 	//counting up how many open spot there are left to try
		// 	for(i = 0; i < 4; i++){
		// 		if(count[i] != -1){
		// 			check++;
		// 		}
		// 	}
		// 	//if there are no more open spots it ends the while loop
		// 	if(check == 0){
		// 		break;
		// 	}
		// 	//get next random spot to check
		// 	spot = this.rand.nextInt(4);
		// }
		// //applying the new direction
		// //if check is 0 then that means that there are no open directions to move
		// if(check == 0){
		// 	return 0;
		// } else{
			return spot;
		// }
	}
	public void spawn(Creature[][] gen){
		//used in doodlebug and ant for spawning
	}
	public int getX(){
		return this.xpos;
	}
	public int getY(){
		return this.ypos;
	}
	public Color getColor(){
		return this.myColor;
	}

}