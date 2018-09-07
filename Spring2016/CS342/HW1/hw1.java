//Main Program execution
import java.io.*;
import java.util.*;
import java.util.Scanner;
public class hw1 {
    private int playerScore;
    private int computerScore;
    private int debug;
    private CardPile deck;
    private CardPile playerHand;
    private CardPile computerHand;
    private CardPile[] piles;
    private String input;
    private String[] splitInput;

    //used to clear the screen before every screen print
    public void clearScreen(){
        final String ANSI_CLS = "\u001b[2J";
        final String ANSI_HOME = "\u001b[H";
        System.out.print(ANSI_CLS + ANSI_HOME);
        System.out.flush();
    }
    //set the debug flag
    public void setDebug(int i){
        this.debug = i;
    }
    // check the debug flag
    public int getDebug(){
        return this.debug;
    }
    // used to shuffle the deck
    public CardPile shuffleDeck(){
        int didntFail = 0;
        CardPile deck = new CardPile(52);
        String[] cards = {"AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "TC", "JC", "QC", "KC", "AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD", "KD", "AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "TH", "JH", "QH", "KH", "AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS", "JS", "QS", "KS"};
        Random rnd = new Random();
        int index = 0;
        for (int i = (cards.length - 1); i > 0; i--){
            index = rnd.nextInt(i + 1);
            String a = cards[index];
            cards[index] = cards[i];
            cards[i] = a;
        }
        for(int i = 0; i < cards.length; i++){
           didntFail = deck.setNewCard(cards[i]);
           if(didntFail == -1){
               System.out.println("TOO MANY CARDS IN PILE");
               return null;
           }
        }
        return deck;
    }
    // used to actually print out the screen which shows the current setup
    public void printScreen(){
        this.clearScreen();
        int computerSize = this.computerHand.getSize();
        if(this.getDebug() == 1){
            System.out.println("DEBUG");
            System.out.println("Computer: " + this.computerHand.printPile() + "|");
        } else {
            System.out.println("Computer: " + computerSize + " cards remaining");
        }
        System.out.println("+--------------+");
        System.out.println("|5   |1   |6   |");
        System.out.println("| " + this.piles[4].getTop() + " | " + this.piles[0].getTop() + " | " + this.piles[5].getTop() + " |");
        System.out.println("|    |    |    |");
        System.out.println("+----+----+----+");
        System.out.println("|2   |Deck|3   |");
        if(this.deck.getSize() > 9){
            System.out.println("| " + this.piles[1].getTop() + " | " + this.deck.getSize() + " | " + this.piles[2].getTop() + " |");
        } else {
            System.out.println("| " + this.piles[1].getTop() + " | 0" + this.deck.getSize() + " | " + this.piles[2].getTop() + " |");
        }
        System.out.println("|    |Left|    |");
        System.out.println("+----+----+----+");
        System.out.println("|7   |4   |8   |");
        System.out.println("| " + this.piles[6].getTop() + " | " + this.piles[3].getTop() + " | " + this.piles[7].getTop() + " |");
        System.out.println("|    |    |    |");
        System.out.println("+--------------+");
        System.out.println("Player: " + this.playerHand.printPile() + "|");
    }
    //Setup function to be called upon every new game
    public int startup(int player){
        int changedPlayer = player;
        this.deck = this.shuffleDeck();
        this.playerHand = new CardPile(52);
        this.computerHand = new CardPile(52);
        this.piles = new CardPile[8];
        Card out;
        if(this.deck == null){
            System.out.println("FAILURE IN SETUP");
            System.exit(1);
        }
        //setting up the playing piles
        for(int i = 0; i < 8; i++){
            this.piles[i] = new CardPile(52);
        }
        //dealing the cards
        for(int i = 0; i < 14; i++){
            out = this.deck.getCard();
            if(player == 1){
                this.playerHand.setNewCard(out.getValue());
                player = 0;
            } else {
                this.computerHand.setNewCard(out.getValue());
                player = 1;
            }
        }
        //setting the four piles that are not in the corners
        this.playerHand.sortHand();
        this.computerHand.sortHand();
        this.piles[0].setNewCard(this.deck.getCard().getValue());
        this.piles[1].setNewCard(this.deck.getCard().getValue());
        this.piles[2].setNewCard(this.deck.getCard().getValue());
        this.piles[3].setNewCard(this.deck.getCard().getValue());
        return changedPlayer + 1;
    }
    //used to make the split input work for any amount of white space
    public String[] sanatize(String[] input){
        String output = new String();
        for(String check: input){
            if(check != null){
                if(!check.equals("")){
                    if(!check.equals(" ")){
                        output += check;
                        output += ",";
                    }
                }
            }
        }
        return output.split(",");
    }
    //debug logging method
    public void debugLog(String message){
        if(this.getDebug() == 1){
            System.out.println(message);
        }
    }
    //used to make sure that the loop isnt infinate
    public boolean alreadyMoved(int[][] inArray, int count, int i, int j){
        for(int k = 0; k <= count; k++){
            if(inArray[k][0] == i && inArray[k][1] == j){
                return true;
            }
        }
        return false;
    }
    //the computer turn program
    public void ai(){
        int step = 1;
        int[][] movedAlready = new int[64][2];
        int count = 0;
        while(step != 6){
            //checking for kings
            if(step == 1){
                this.debugLog("Step 1");
                if(this.computerHand.kingCount() > 0){
                    Card[] kings = this.computerHand.kingSearch();
                    char[] piles = {'1','2','3','4'};
                    int retval;
                    for(Card king: kings){
                        if(king != null){
                            for(char i: piles){
                                this.debugLog("ATTEMPTING TO LAY " + king.getValue() + " ON PILE " + String.valueOf(i));
                                retval = this.layOnPile(this.computerHand, king.getValue(), String.valueOf(i));
                            }
                        }
                    }
                }
                int[] piles = {1, 2, 3, 4};
                for(int i: piles){
                    if(this.piles[i - 1].getBottom().charAt(0) == 'K'){
                        int[] kingPiles = {5, 6, 7, 8};
                        for(int j: kingPiles){
                            this.debugLog("ATTEMPTING TO MOVE PILE " + i + " ON PILE " + j);
                            int retval = this.moveOnto(i - 1, j - 1);
                        }
                    }
                }
                step = 2;
            } else if(step == 2){
                this.debugLog("Step 2");
                int[] piles = {1,2,3,4,5,6,7,8};
                int retval;
                step = 3;
                for(int i:piles){
                    for(int j:piles){
                        if(step == 2){
                            continue;
                        }
                        if(this.piles[i-1].getBottom().charAt(0) == 'K' && (j == 1 || j == 2 || j == 3 || j == 4)){
                            continue;
                        }
                        if(i != j && !this.alreadyMoved(movedAlready, count, i, j)){
                            this.debugLog("ATTEMPTING TO MOVE PILE " + i + " ON PILE " + j);
                            retval = this.moveOnto(i, j);
                            if(retval != 0){
                                step = 3;
                            } else {
                                movedAlready[count][0] = i;
                                movedAlready[count][1] = j;
                                count++;
                                step = 2;
                            }
                        }
                    }
                }
            } else if (step == 3){
                this.debugLog("Step 3");
                count = 0;
                String[] currentHand = this.computerHand.printPile().split(" ");
                for(String cardVal:currentHand){
                    for(char i = '1'; i < '9'; i++){
                        if(step == 3){
                            if(!this.piles[Integer.parseInt(String.valueOf(i)) - 1].equals("  ")){
                                this.debugLog("ATTEMPTING TO LAY " + cardVal + " ON PILE " + String.valueOf(i));
                                int retval = this.layOnPile(this.computerHand, cardVal, String.valueOf(i));
                                if(retval == 0){
                                    step = 2;
                                }
                            }
                        }
                    }
                }
                if(step == 3){
                    step = 4;
                }
            } else if (step == 4){
                this.debugLog("Step 4");
                String[] currentHand = this.computerHand.printPile().split(" ");
                for(String cardVal:currentHand){
                    for(char i = '1'; i < '9'; i++){
                        if(step == 4){
                            if(this.piles[Integer.parseInt(String.valueOf(i)) - 1].equals("  ")){
                                this.debugLog("ATTEMPTING TO LAY " + cardVal + " ON PILE " + String.valueOf(i));
                                int retval = this.layOnPile(this.computerHand, cardVal, String.valueOf(i));
                                if(retval == 0){
                                    step = 2;
                                }
                            }
                        }
                    }
                }
                if(step == 4){
                    step = 5;
                }
            } else if(step == 5){
                this.debugLog("Step 5");
                if(this.computerHand.getSize() > 0){
                    Card newCard = this.deck.getCard();
                    if(newCard != null){
                        this.debugLog("ADDING CARD " + newCard.getValue() + " TO THE COMPUTER'S HAND");
                        this.computerHand.setNewCard(newCard.getValue());
                    }
                }
                step = 6;
            }
        }
    }
    // print out the desplay with some log message and wait for input
    public void printOut(Scanner playerInput, String message){
        this.playerHand.sortHand();
        this.computerHand.sortHand();
        this.printScreen();
        System.out.println(message);
        System.out.print("Move> ");
        this.input = playerInput.next();
        this.input = this.input.toUpperCase();
        this.splitInput = input.split(" ");
        this.splitInput = this.sanatize(splitInput);
    }
    // get the input string
    public String getInput(){
        return this.input;
    }
    //setting the input raw string in an upper case version
    public void setInput(String inString){
        this.input = inString.toUpperCase();
    }
    //used to get the array that is the split input for processing
    public String[] getSplitInput(){
        return this.splitInput;
    }
    //checking whether or not two cards can be put on 
    public int checkConnection(String pileTop, Card card){
        char cardSuit = card.getValue().charAt(1);
        char cardValue = card.getValue().charAt(0);
        int cardHex = card.getHex();
        if(pileTop.equals("  ")){
            if(cardValue != 'K'){
                return 3;
            } else {
                return 0;
            }
        } else {
            char pileTopSuit = pileTop.charAt(1);
            char pileTopValue = pileTop.charAt(0);
            int pileTopHex = 0;
            if(pileTopValue == 'A'){
                pileTopHex = 0x1;
            } else if(pileTopValue == '2'){
                pileTopHex = 0x2;
            } else if(pileTopValue == '3'){
                pileTopHex = 0x3;
            } else if(pileTopValue == '4'){
                pileTopHex = 0x4;
            } else if(pileTopValue == '5'){
                pileTopHex = 0x5;
            } else if(pileTopValue == '6'){
                pileTopHex = 0x6;
            } else if(pileTopValue == '7'){
                pileTopHex = 0x7;
            } else if(pileTopValue == '8'){
                pileTopHex = 0x8;
            } else if(pileTopValue == '9'){
                pileTopHex = 0x9;
            } else if(pileTopValue == 'T'){
                pileTopHex = 0xA;
            } else if(pileTopValue == 'J'){
                pileTopHex = 0xB;
            } else if(pileTopValue == 'Q'){
                pileTopHex = 0xC;
            } else if(pileTopValue == 'K'){
                pileTopHex = 0xD;
            }
            if(pileTopSuit == 'C' && (cardSuit != 'D' && cardSuit != 'H')){
                this.debugLog("CARD NOT DIMOND OR HEART " + cardValue + cardSuit + " " + pileTopValue + pileTopSuit);
                return 3;
            } else if(pileTopSuit == 'S' && (cardSuit != 'D' && cardSuit != 'H')){
                this.debugLog("CARD NOT DIMOND OR HEART " + cardValue + cardSuit + " " + pileTopValue + pileTopSuit);
                return 3;
            } else if(pileTopSuit == 'D' && (cardSuit != 'C' && cardSuit != 'S')){
                this.debugLog("CARD NOT CLUBS OR SPADES " + cardValue + cardSuit + " " + pileTopValue + pileTopSuit);
                return 3;
            } else if(pileTopSuit == 'H' && (cardSuit != 'C' && cardSuit != 'S')){
                this.debugLog("CARD NOT CLUBS OR SPADES " + cardValue + cardSuit + " " + pileTopValue + pileTopSuit);
                return 3;
            } else if(pileTopHex != cardHex + 0x1){
                this.debugLog("BAD CARD VALUE " + pileTopHex + " " + cardHex + " " + (cardHex + 0x1));
                return 3;
            }
        }
        return 0;
    }
    //Used to safely parse ints
    public boolean safeParse(String text, int out){
        try {
            out = Integer.parseInt(text);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
    // used to put one card form a players hand onto a pile
    public int layOnPile(CardPile hand, String card, String pile){
        int pileInt = -1;
        if(!this.safeParse(pile, pileInt)){
            return 1;
        }
        pileInt = Integer.parseInt(pile);
        if(pileInt < 1 || pileInt > 8){
            return 2;
        }
        card = card.toUpperCase();
        if((pileInt == 5 || pileInt == 6 || pileInt == 7 || pileInt == 8) && (this.piles[pileInt - 1].getTop().equals("  ") && card.charAt(0) != 'K')){
            this.debugLog("MOVING NON KING ONTO KING BASE ONLY EMPTY PILE " + pileInt);
            return 3;
        }
        Card retval = hand.search(card);
        if(retval == null){
            return 1;
        }
        String pileTop = new String(this.piles[pileInt - 1].getTop());
        int secondRetval = this.checkConnection(pileTop, retval);
        if(secondRetval > 0){
            hand.setNewCard(retval.getValue());
            return secondRetval;
        }
        this.debugLog("ADDING " + retval.getValue() + " TO PILE " + pileInt);
        this.piles[pileInt - 1].setNewCard(retval.getValue());
        return 0;
    }
    //used to move one pile onto another
    public int moveOnto(int fromPile, int toPile){
        if(fromPile < 1 || fromPile > 8){
            return 2;
        }
        if(toPile < 1 || toPile > 8){
            return 3;
        }
        if((toPile == 5 || toPile == 6 || toPile == 7 || toPile == 8) && (this.piles[toPile - 1].getTop().equals("  ") && this.piles[fromPile - 1].getBottom().charAt(0) != 'K')){
            this.debugLog("MOVING NON KING ONTO KING BASE ONLY EMPTY PILE " + toPile);
            return 1;
        }
        String fromCard = this.piles[fromPile - 1].getBottom();
        String toCard = this.piles[toPile - 1].getTop();
        Card checkCard = new Card();
        checkCard.setValue(fromCard);
        int retval = this.checkConnection(toCard, checkCard);
        if(retval > 0){
            return retval + 3;
        }

        while(this.piles[fromPile - 1].getSize() != 0){
            //System.out.println(this.piles[fromPile - 1].getSize());
            String card = this.piles[fromPile - 1].getBottomCard();
            this.piles[toPile - 1].setNewCard(card);
        }
        return 0;
    }
    //main function
    public static void main (String[] args) {
        hw1 running = new hw1();
        Scanner playerInput = new Scanner(System.in).useDelimiter("\\n");
        running.clearScreen();
        if(args.length > 0){
            if(args[0].equals("-d")){
                running.setDebug(1);
            } else {
                running.setDebug(0);
            }
        }
        running.playerScore = 0;
        running.computerScore = 0;
        int dealer = 0;
        int player = running.startup(dealer);
        dealer = 1;
        running.printOut(playerInput, "");
        while(running.playerScore > -25 || running.computerScore > -25){
            if(player == 0){
                running.ai();
                player = 1;
                if(running.computerHand.getSize() == 0){
                    int kingCount = running.computerHand.kingCount();
                    if(kingCount > 0){
                        running.playerScore -= kingCount * 10;
                    }
                    running.playerScore -= running.playerHand.getSize() - kingCount;
                    player = running.startup(dealer);
                    running.printOut(playerInput, "COMPUTER WON PREVIOUS ROUND\nSCORE:\n\tPLAYER: " + running.playerScore + "\n\tComputer: " + running.computerScore);
                    if(dealer == 0){
                        dealer = 1;
                    } else {
                        dealer = 0;
                    }
                } else {
                    running.printOut(playerInput, "");
                }
            } else {
                if(running.getInput().equals("Q")){
                    System.out.print("Are you sure?> ");
                    running.setInput(playerInput.next());
                    if(running.getInput().equals("Y")){
                        System.out.println("Thanks for playing");
                        System.exit(1);
                    }
                } else if(running.getInput().equals("H")){
                    running.printOut(playerInput, "Q - Quit the program.\nH - Help\nA - About\nD - Draw a Card from the Draw Pile\nL <Card> <Pile> - Lay a Card on a Pile\nM <Pile1> <Pile2> - Move One Pile on top of another pile.\nE <Pile> - Lists the cards on any one pile");
                } else if(running.getInput().equals("A")){
                    running.printOut(playerInput, "About me and the program\nName - Maxwell Petersen\nNetID - mpeter39\nProgram - Card Game: Kings in the Corner\nHomework number - 1\n");
                } else if(running.getInput().equals("D")){ 
                    Card newCard = running.deck.getCard();
                    if(newCard != null){
                        running.playerHand.setNewCard(newCard.getValue());
                    }
                    player = 0;
                } else if(running.getSplitInput()[0].equals("L")){
                    if(running.getSplitInput().length < 3){
                        running.printOut(playerInput, "NOT ENOUGH ARGUMENTS TO LAY A CARD ON A PILE");
                    } else{
                        int retval = running.layOnPile(running.playerHand, running.getSplitInput()[1], running.getSplitInput()[2]);
                        if(retval == 0){
                            running.printOut(playerInput, new String(running.getSplitInput()[1] + " SUCESSFULLY PUT ON PILE: " + running.getSplitInput()[2]));
                        } else if(retval == 1){
                            running.printOut(playerInput, new String(running.getSplitInput()[1] + " IS NOT A CARD IN YOUR HAND"));
                        } else if(retval == 2){
                            running.printOut(playerInput, new String(running.getSplitInput()[2] + " IS NOT A VALID PILE SELECTION"));
                        } else if(retval == 3){
                            running.printOut(playerInput, new String(running.getSplitInput()[1] + " CANNOT BE PUT ON PILE: " + running.getSplitInput()[2]));
                        }
                    }
                } else if(running.getSplitInput()[0].equals("E")){
                    int pileNumber = 0;
                    String message = "";
                    if(running.safeParse(running.getSplitInput()[1], pileNumber)){
                        pileNumber = Integer.parseInt(running.getSplitInput()[1]);
                        if(pileNumber < 1 || pileNumber > 8){
                            message = "PILE NUMBER OUT OF BOUNDS CANNOT EXPAND";
                        } else {
                            message = "PRINTOUT OF PILE: " + pileNumber + " | " + running.piles[pileNumber - 1].printPile() + "|";
                        }
                    } else {
                        message = "NOT VALID NUMBER FORMAT";
                    }
                    running.printOut(playerInput, message);
                } else if(running.getSplitInput()[0].equals("M")){
                    String message;
                    if(running.getSplitInput().length < 3){
                        message = "IMPROPER USAGE NEED TWO PILES GIVEN";
                    } else{
                        int from = 0;
                        int to = 0;
                        if(running.safeParse(running.getSplitInput()[1], from) || running.safeParse(running.getSplitInput()[2], to)){
                            from = Integer.parseInt(running.getSplitInput()[1]);
                            to = Integer.parseInt(running.getSplitInput()[2]);
                            int retval = running.moveOnto(from, to);
                            if(retval == 1){
                                message = "NOT A PROPER FROM PILE SUPPLIED FOR MOVING A KING BASED PILE PLEASE SELECT FROM 1, 2, 3, AND 4";
                            } else if (retval == 2){
                                message = "FROM PILE OUT OF RANGE PLEASE ONLY SELECT 1, 2, 3, AND 4";
                            } else if (retval == 3){
                                message = "TO PILE OUT OF RANGE PLEASE ONLY SELECT 1-8";
                            } else if (retval == 6){
                                message = "ERROR IN CARD COMBINATION PLEASE SEE RULES FOR MORE DETAILS";
                            } else {
                                message = "SUCESS IN MOVING PILE: " + running.getSplitInput()[1] + " ONTO PILE: " + running.getSplitInput()[2];
                            }
                        } else {
                            message = "NOT VALID NUMBERS GIVEN";
                        }
                    }
                    running.printOut(playerInput, message);
                } else if (running.playerHand.getSize() == 0){
                    int kingCount = running.computerHand.kingCount();
                    if(kingCount > 0){
                        running.computerScore -= kingCount * 10;
                    }
                    running.computerScore -= running.computerHand.getSize() - kingCount;
                    player = running.startup(dealer);
                    running.printOut(playerInput, "PLAYER WON PREVIOUS ROUND\nSCORE:\n\tPLAYER: " + running.playerScore + "\n\tComputer: " + running.computerScore);
                    if(dealer == 0){
                        dealer = 1;
                    } else {
                        dealer = 0;
                    }
                } else {
                    running.printOut(playerInput, "");
                }
            }
        }
        if(running.computerScore <= -25){
            System.out.println("PLAYER WON THIS GAME\nSCORE:\n\tPlayer: " + running.playerScore + "\n\tComputer: " + running.computerScore);
        } else {
            System.out.println("COMPUTER WON THIS GAME\nSCORE:\n\tPlayer: " + running.playerScore + "\n\tComputer: " + running.computerScore);
        }
    }
}
