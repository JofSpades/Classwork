/****************************************************************
 *Class to store and preform all information about a single card*
 ****************************************************************
 */
public class Card {
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
    private int value;
    private String name;
    
    //constructor class
    public Card(){
        this.value = -1;
        this.name = "  ";
    }
    //returns the string representation of the card
    public String getValue(){
        return this.name;
    }
    //return the int representation of the card
    public int getHex(){
        return this.value;
    }
    //converts the input string into the hex values of the enums
    //then stores both
    public void setValue (String newValue){
        this.name = newValue;
        if(newValue.charAt(0) == 'A'){
            this.value = IS_ACE;
        } else if(newValue.charAt(0) == '2'){
            this.value = IS_TWO;
        } else if(newValue.charAt(0) == '3'){
            this.value = IS_THREE;
        } else if(newValue.charAt(0) == '4'){
            this.value = IS_FOUR;
        } else if(newValue.charAt(0) == '5'){
            this.value = IS_FIVE;
        } else if(newValue.charAt(0) == '6'){
            this.value = IS_SIX;
        } else if(newValue.charAt(0) == '7'){
            this.value = IS_SEVEN;
        } else if(newValue.charAt(0) == '8'){
            this.value = IS_EIGHT;
        } else if(newValue.charAt(0) == '9'){
            this.value = IS_NINE;
        } else if(newValue.charAt(0) == 'T'){
            this.value = IS_TEN;
        } else if(newValue.charAt(0) == 'J'){
            this.value = IS_JACK;
        } else if(newValue.charAt(0) == 'Q'){
            this.value = IS_QUEEN;
        } else if(newValue.charAt(0) == 'K'){
            this.value = IS_KING;
        }
    }
}

