import java.io.*;
public class CardPile{
    //static hex representation of each card type to allow for faster sorting
    private static int IS_ACE = 0x1;
    private static int IS_TWO = 0x2;
    private static int IS_THREE = 0x3;
    private static int IS_FOUR = 0x4;
    private static int IS_FIVE = 0x5;
    private static int IS_SIX = 0x6;
    private static int IS_SEVEN = 0x7;
    private static int IS_EIGHT = 0x8;
    private static int IS_NINE = 0x9;
    private static int IS_TEN = 0xA;
    private static int IS_JACK = 0xB;
    private static int IS_QUEEN = 0xC;
    private static int IS_KING = 0xD;
    private Card[] pile;
    private int lastCard;
    private int sizeOfPile;
    //construstor method
    public CardPile(int size){
        this.sizeOfPile = size;
        this.pile = new Card[size + 1];
        for(int i = 0; i <= this.sizeOfPile; ++i){
            this.pile[i] = new Card();
        }
        this.lastCard = -1;
    }
    // adds a new card to the pile
    public int setNewCard(String value){
        if(this.lastCard == this.sizeOfPile + 1){
            return -1;
        } else {
            this.lastCard++;
            this.pile[this.lastCard].setValue(value);
            return 1;
        }
    }
    //removes the top card off the pile
    public Card getCard(){
        if(this.lastCard >= 0){
            Card currentCard = this.pile[this.lastCard];
            this.lastCard--;
            return currentCard;
        } else if (this.lastCard == -1){
            //System.out.println("NO MORE CARDS TO DRAW");
            return null;
        } else { 
            System.out.println("IMPROPER CALL TO getCard() NOT ENOUGH CARDS");
            System.exit(1);
        }
        return null;
    }
    //returns how many carsd are in the pile
    public int getSize(){
        return this.lastCard + 1;
    }
    //returns the string representation of the top card of any pile
    public String getTop(){
        if(this.lastCard >= 0){
            return this.pile[this.lastCard].getValue();
        } else {
            return "  ";
        }
    }
    //used to print out the entire contents of the pile
    public String printPile(){
        String out = new String();
        for(int i = 0; i < this.lastCard + 1; i++){
            out += this.pile[i].getValue();
            out += " ";
        }
        return out;
    }
    //used to sort hand
    public void quickSort(int lowerIndex, int higherIndex){
        int i = lowerIndex;
        int j = higherIndex;
        int pivot = this.pile[lowerIndex+(higherIndex-lowerIndex)/2].getHex();
        while(i < j){
            while(this.pile[i].getHex() > pivot){
                i++;
            }
            while(this.pile[j].getHex() < pivot){
                j--;
            }
            if(i <= j){
                Card tmp = this.pile[i];
                this.pile[i] = this.pile[j];
                this.pile[j] = tmp;
                i++;
                j--;
            }
        }
        if (lowerIndex < j){
            this.quickSort(lowerIndex, j);
        } if (i < higherIndex){
            this.quickSort(i, higherIndex);
        }
    }
    //wrapper function on calling quicksort
    public void sortHand(){
        this.quickSort(0, this.lastCard);
        Card tmp;
    }
    // used to count how many kings are left for scoring purposes
    public int kingCount(){
        int count = 0;
        for(int i = 0; i <= this.lastCard; i++){
            if(this.pile[i].getHex() == IS_KING){
                count++;
            }
        }
        return count;
    }
    // used to search through the pile looking for a card and if found will remove it from the pile
    public Card search(String lookingFor){
        for(int i = 0; i <= this.lastCard; i++){
            if(this.pile[i].getValue().equals(lookingFor)){
                Card tmp = this.pile[i];
                this.pile[i] = this.pile[this.lastCard];
                this.pile[this.lastCard] = tmp;
                this.lastCard--;
                return tmp;
            }
        }
        return null;
    }
    //returns the bottom of the pile
    public String getBottom(){
        return this.pile[0].getValue();
    }
    //returns the card at the bottom of the pile
    public String getBottomCard(){
        String outCard = this.pile[0].getValue();
        for(int i = 1; i <= this.lastCard; i++){
            //System.out.println(this.pile[i - 1].getValue() + " " + this.pile[i].getValue());
            this.pile[i - 1] = this.pile[i];
        }
        this.lastCard--;
        return outCard;
    }
    //returns pointers to all the kings in the hand
    public Card[] kingSearch(){
        Card[] kings = new Card[4];
        int count = 0;
        for(int i = 0; i < this.getSize(); i++){
            if(this.pile[i].getValue().charAt(0) == 'K'){
                kings[count] = this.pile[i];
                count++;
            }
        }
        return kings;
    }
}
