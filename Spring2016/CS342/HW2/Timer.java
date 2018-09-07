import java.util.*;

//timer and score updater
public class Timer implements Runnable {
	private Score scoreInstance;
	private MineSweeper mainInstance;

	// needed for threads
	public void run() {
		while (this.scoreInstance.isGameRunning()) {
			try {
				Thread.sleep(998);
				this.scoreInstance.setScore(this.scoreInstance.getScore() + 1);
			} catch (InterruptedException e) {
				System.out.println("TIMER FAILED EXITING");
				System.exit(1);
			}
			this.mainInstance.updateTime();
		}
	}

	// pulls in the instance of Score being used by the program
	public Timer(Score passedInInstance, MineSweeper passedInMain) {
		this.scoreInstance = passedInInstance;
		this.mainInstance = passedInMain;
	}
}
