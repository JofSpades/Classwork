#include <stdio.h>
#include <math.h>

int main (int argc, int argv[]){

	int myint;
	char mychar;
	int *myptr;

	unsigned long int maxInt = (unsigned long)pow(2, 8 * sizeof(myint)) - 1;
	unsigned long int maxChar = (unsigned long)pow(2, 8 * sizeof(mychar)) - 1;
	unsigned long int maxPtr = pow(2, 8 * sizeof(myptr));

	printf("Size of myint: %lu bytes\n", sizeof(myint));
	printf("Size of mychar: %lu bytes\n", sizeof(mychar));
	printf("Size of myptr: %lu bytes\n", sizeof(myptr));

	printf("Max stored in myint: %lu or 0x%lx\n", maxInt, maxInt);
	printf("Max stored in mychar: %lu or 0x%lx\n", maxChar, maxChar);
	printf("Max stored in myptr: %lu or 0x%lx\n", maxPtr, maxPtr);

	return 0;
}
