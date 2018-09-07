import java.io.*;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.io.Serializable;

//class for reading and writing the saved data
public class SavedData implements Serializable {
	private static final long serialVersionUID = 6128016096756071380L;
	private int[] savedScores;
	private String[] savedNames;

	// initializes the save file when the load fails at any point
	private SavedData newFile() {
		// makes a new array to store the default values
		int[] newFileData = new int[10];
		String[] newFileNames = new String[10];

		// for length of the array set all values to ridiculously high score
		// that no one will reach
		for (int i = 0; i < 10; i++) {
			int n = i + 1;
			newFileData[i] = 999999;
			newFileNames[i] = "Player " + n;
		}
		// return a new object that has the initialized array for a "new" file
		return new SavedData(newFileData, newFileNames);
	}

	// used to load in the data from file
	private SavedData loadData() {
		// deceleration for a spot of the retrieved object
		SavedData restoredData;

		// this is why I don't like Java
		// try opening/finding the old save file
		try {
			FileInputStream saveFile = new FileInputStream("saveFile.sav");

			// try opening a connection to the old save file if found
			try {
				ObjectInputStream restore = new ObjectInputStream(saveFile);

				// try restoring the object data
				try {
					restoredData = (SavedData) restore.readObject();
					// one catch which just makes a new file
				} catch (IOException io) {
					restoredData = this.newFile();
					// second catch which will make a new file
				} catch (ClassNotFoundException noClass) {
					restoredData = this.newFile();
				}
				// if you make it here it needs to be closed
				restore.close();
				// catch for IO error makes new file
			} catch (IOException io) {
				restoredData = this.newFile();
			}
			// catch for empty file makes a new one
		} catch (NullPointerException nullPointer) {
			restoredData = this.newFile();
			// catch for unable to make/open an old file makes a new one
		} catch (FileNotFoundException noFile) {
			restoredData = this.newFile();
		}
		// return a pointer to either a new file or the retrieved object
		return restoredData;
	}

	// return the full list of top scores
	public int[] getTopScore() {
		return this.savedScores;
	}

	public String[] getTopNames() {
		return this.savedNames;
	}

	// used to update the listings of top ten
	public void updateTop(int playerScore, String playerName) {
		// for every element in the top ten
		for (int i = 0; i < 10; i++) {
			// if the current score is less than or equal to the currently
			// observed score and not the end
			if (playerScore <= this.savedScores[i] && i != 9) {
				// for the remaining elements in the list starting at the end
				for (int j = 8; j >= i; j--) {
					// move everything back one spot
					this.savedScores[j + 1] = this.savedScores[j];
					this.savedNames[j + 1] = this.savedNames[j];
				}
				// set the current i score in the top ten to the current score
				this.savedScores[i] = playerScore;
				this.savedNames[i] = playerName;
				// prevent the check for it being less from continuing
				return;
				// less than the last spot in the top ten
			} else if (playerScore <= this.savedScores[i] && i != 9) {
				// set the last spot to the current score
				this.savedScores[9] = playerScore;
				this.savedNames[9] = playerName;
				// prevent the check for it being less from continuing
				return;
			}
		}
	}

	// Mainly used constructor that will open up a save file and read in the
	// saved data
	public SavedData() {
		this.savedScores = new int[10];
		this.savedNames = new String[10];
		SavedData restoredData = this.loadData();

		this.savedScores = restoredData.getTopScore();
		this.savedNames = restoredData.getTopNames();
	}

	// create the object with an initial set of data thus not requiring the
	// looking of files
	private SavedData(int[] givenData, String[] names) {
		this.savedScores = givenData;
		this.savedNames = names;
	}

	// used to save the object to file so it can be stored for later use
	public void saveData() {
		SavedData instance = new SavedData(this.savedScores, this.savedNames);
		// trying to open/find the save file
		try {
			FileOutputStream saveFile = new FileOutputStream("saveFile.sav");

			// try to make a new connection to that file
			try {
				ObjectOutputStream save = new ObjectOutputStream(saveFile);

				// try to save to that file
				try {
					save.writeObject(instance);
					// catch in saving forcing exit
				} catch (IOException io) {
					System.out.println(io);
					System.out.println("*****SAVE FILE FAILED IN WRITING*****");
					System.out.println("***************EXITING***************");
					System.exit(1);
				}
				// close the connection to the file
				save.close();
				// catch in opening the data stream forcing exit
			} catch (IOException io) {
				System.out.println("*****SAVE FILE FAILED IN OPENING UP SAVE STREAM*****");
				System.out.println("***********************EXITING**********************");
				System.exit(1);
			}
			// catch in opening/finding the file forcing exit
		} catch (FileNotFoundException noFile) {
			System.out.println("*****SAVE FILE FAILED IN CREATION*****");
			System.out.println("***************EXITING****************");
			System.exit(1);
		}
	}
}
