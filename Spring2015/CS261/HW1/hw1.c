/*********************************************
|    Maxwell Petersen                        |
|    UIN: 662607465                          |
|    CS 261                                  |
|    HW 1 Due: 1/23/15 11:59AM               |
|    The parts for 1 and 2 are marked        |
|    before each function with the           |
|    respective part number and a short      |
|    explination of the thought process.     |
|    Questions 3 and 4 are in the            |
|    comments below the main function and    |
|    will also be the last bit of output     |
|    from when you run this program.         |
*********************************************/ 

#include <stdio.h>

//1.A

int HasOne (int in){
   /*

   By preforming the ! twice when the value for x is 0 the output would first be
   1 then with the second ! the output would become 0, vice versa occurs for when
   x is a non-zero value(meaning there is at least one 1 in the bits of it)

   */
   return (! (!in));

}

//1.B

int EightToFifteenHasOne (int in){

   /*

   Shifting to the left to remove all of the bits to the right of the 8th then to
   the roght to remove all unneded values from the left. 

   */

   return (! (!((in >> 8) << 24)));

}

//1.C

int LastNibbleCompare (int in, int ask){

   /*

   To handle the case of 15 being the possible value the bits for both x and y will
   be shifted to make sure the trailing 1's are not a problem for the x value.

   */

   return (((in >> 28) << 28) && (ask << 28));

}

//2

int NthNibble (int in, int index){

   /*

   By shifting to the right it makes the needed nibble lest signifigant and for any
   1's that shiw up by preforming the & 0xF operation i get the nibble in its proper
   place and no need to worry about extra 1's

   */

   int shiftR = (index << 2);

   return ((in >> shiftR) & 0xF); 

}

int main(int argc, char *argv[]) {

   int testOneT = 900;
   int testOneF = 0;
   int testTwoT = 1536;
   int testTwoF = 36;
   int testTwoFTwo = 131072;
   int testThreeT = 2147483648;
   int testThreeF = 0;
   int testThreeTest = 8;
   int testFourIn = 686486435;
   int testFourCheck = 5;

   printf("FOR ALL FOLLOWING ANSWERS\n1 IS DEFINED AS TRUE\n0 IS DEFINED AS FALSE\n");
   printf("Does %d have a 1 in it? %d (should be 1)\n", testOneT, HasOne(testOneT));
   printf("Does %d have a 1 in it? %d (should be 0)\n", testOneF, HasOne(testOneF));
   printf("Does %d have a 1 between the 8th and 15th bit? %d (should be 1)\n", testTwoT, EightToFifteenHasOne(testTwoT));
   printf("Does %d have a 1 between the 8th and 15th bit? %d (should be 0)\n", testTwoF, EightToFifteenHasOne(testTwoF));
   printf("Does %d have a 1 between the 8th and 15th bit? %d (should be 0)\n", testTwoFTwo, EightToFifteenHasOne(testTwoFTwo));
   printf("Is there a %d in the last nibble of %d? %d (should be 1)\n", testThreeTest, testThreeT, LastNibbleCompare(testThreeT, testThreeTest));
   printf("Is there a %d in the last nibble of %d? %d (should be 0)\n", testThreeTest, testThreeF, LastNibbleCompare(testThreeF, testThreeTest));
   printf("The %d nibble from %d is 0x%x. (should be 0xE)", testFourCheck, testFourIn, NthNibble(testFourIn, testFourCheck));
   printf("QUESTION 3:\n**********************************************\n| decimal | binary             | hexadecimal |\n|  37     | 0b0000000000100101 | 0x0025      |\n| -37     | 0b1111111111011010 | 0xFFDB      |\n| -29642  | 0b1100011000110110 | 0xC636      |\n|  2580   | 0b0000101000010100 | 0x0A14      |\n| -137    | 0b1111111101110110 | 0xFF76      |\n| -32680  | 0b1100000000101100 | 0xC02C      |\n|  5589   | 0b0001010111010101 | 0x15D5      |\n**********************************************\n");
   printf("QUESTION 4:\n***************************************************\n| decimal     | binary              | hexadecimal |\n| -37.125     | 0b00100101.00100000 | 0x25.20     |\n|  37.125     | 0b11011010.11100000 | 0xDA.E0     |\n| -19.8203125 | 0b11101100.00101110 | 0xEC.2E     |\n|  11.7617188 | 0b00001011.11000011 | 0x0B.C3     |\n| -99.6       | 0b10011100.01100111 | 0xAC.67     |\n| -31.3710938 | 0b11100000.10100001 | 0xE0.A1     |\n|  53.3007813 | 0b00110101.01001101 | 0x35.4D     |\n***************************************************");

 return 0;  
}

// 3

/*********************************************
| decimal | binary             | hexadecimal |
|  37     | 0b0000000000100101 | 0x0025      |
| -37     | 0b1111111111011010 | 0xFFDB      |
| -29642  | 0b1100011000110110 | 0xC636      |
|  2580   | 0b0000101000010100 | 0x0A14      |
| -137    | 0b1111111101110110 | 0xFF76      |
| -32680  | 0b1100000000101100 | 0xC02C      |
|  5589   | 0b0001010111010101 | 0x15D5      |
*********************************************/

// 4

/**************************************************
| decimal     | binary              | hexadecimal |
| -37.125     | 0b00100101.00100000 | 0x25.20     |
|  37.125     | 0b11011010.11100000 | 0xDA.E0     |
| -19.8203125 | 0b11101100.00101110 | 0xEC.2E     |
|  11.7617188 | 0b00001011.11000011 | 0x0B.C3     |
| -99.6       | 0b10011100.01100111 | 0xAC.67     |
| -31.3710938 | 0b11100000.10100001 | 0xE0.A1     |
|  53.3007813 | 0b00110101.01001101 | 0x35.4D     |
**************************************************/

