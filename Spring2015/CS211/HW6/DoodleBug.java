import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
class DoodleBug extends Creature{
	private int daysLastEat;
	public DoodleBug(int x, int y){
		super(x, y);
		this.myColor = new Color(255,0,0);
		this.daysLastEat = 0;
	}
	private int canIEat(int x, int y, Creature[][] gen){
		if(x > 0 && x < 20 && y > 0 && y < 20){
			if(gen[x][y] != null){
				if(gen[x][y].getClass() == Ant.class){
					return 1;
				}
			}
		}
		return 0;
	}
	private int hunt(Creature[][] gen){
		int i;
		for(i = 0; i < 4; i++){
			if(canIEat(this.xpos+location[i][0], this.ypos + location[i][1], gen) == 1){
				return i;
			}
		}
		return -1;
	}
	public void move(Creature[][] gen, Creature[][] genPlus){
		int hunt = -1;
		if(hunt == -1){
			super.move(gen, genPlus);
		} else {
			if(hunt == 0){
				this.ypos += 1;
				this.daysLastEat = 0;
			} else if(hunt == 1){
				this.xpos += 1;
				this.daysLastEat = 0;
			} else if(hunt == 2){
				this.ypos -= 1;
				this.daysLastEat = 0;
			} else if(hunt == 3){
				this.xpos -= 1;
				this.daysLastEat = 0;
			}
		}
		this.setColor();
	}
	public void spawn(Creature[][] gen){
		int locationMod = super.spawn(gen, 8);
		int newXpos = (location[locationMod][0]) + xpos;
		int newYpos = (location[locationMod][0]) + ypos;
		gen[newXpos][newYpos] = new DoodleBug(newXpos, newYpos);
	}
	public int howHungry(){
		return this.daysLastEat;
	}
	public void setColor(){
		Color inColor = new Color((255-(daysLastEat*85)),0,0);
		myColor = inColor;
	}
}