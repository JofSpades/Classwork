import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;
import java.util.*;
class Ant extends Creature{
	public Ant(int x, int y){
		super(x, y);
		this.myColor = Color.GREEN;
	}
	public void spawn(Creature[][] gen){
		int locationMod = super.spawn(gen, 8);
		int newXpos = (location[locationMod][0]) + xpos;
		int newYpos = (location[locationMod][0]) + ypos;
		gen[newXpos][newYpos] = new Ant(newXpos, newYpos);
	}
}