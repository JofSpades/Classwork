import java.io.*;

//this class is meant to be the handler for the keep track of the score
public class Score {
	private int[] topTen;
	private String[] topNames;
	private int current;
	private SavedData saveFile;
	private boolean start;
	private boolean won;

	// get method for current score
	public int getScore() {
		// returns the current score
		return this.current;
	}

	// get method for top scores
	public int[] getTopScore() {
		// return the current top ten at the start of the game
		return this.topTen;
	}

	public String[] getTopNames() {
		return this.saveFile.getTopNames();
	}

	// set method for current score
	public void setScore(int score) {
		// increases the score
		this.current += score;
	}

	// notice for the game has started
	public void gameStart(MineSweeper instance) {
		// lets the thread run forever
		this.start = true;
		// starts the thread on this instance of Score
		(new Thread(new Timer(this, instance))).start();
	}

	// notice for the game to end and cleanup with save
	public void gameEnd(String name) {
		// gets the thread to stop eventually
		this.start = false;
		// check for high score
		this.saveFile.updateTop(this.current, name);

		// save data to the file if winner
		if (this.won) {
			this.saveFile.saveData();
		}
	}

	// sets the won flag to true if the game is finishing because of the player
	// winning
	public void didWin() {
		this.won = true;
	}

	// get method for start variable
	public boolean isGameRunning() {
		// used to verify that the game is still running by the thread
		return this.start;
	}

	// used to keep track of the score
	public void checkHighScore(String name) {
		// used to see if the current score is in the top ten
		// only called when the game is ending and player has won
		this.saveFile.updateTop(this.current, name);
	}

	// constructor method
	public Score() {
		this.won = false;
		this.start = false;
		// this.topTen = new int[10];

		this.current = 0;
		this.saveFile = new SavedData();
		this.topTen = this.saveFile.getTopScore();
		this.topNames = this.saveFile.getTopNames();
	}
}
