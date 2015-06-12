#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define CHAR_COUNT 27

// Used to take in a number and give a char back.
// The purpose of this function is to return a character value for whatever integer is passed in.
// Because the ability to take a ciphered number and replace it with its char value is important
// for encryption but also decryption.
char pickAChar(long choice)
{
    if(choice == 0)
        return ' ';
    else if(choice == 1)
        return 'Z';
    else if(choice == 2)
        return 'Y';
    else if(choice == 3)
        return 'X';
    else if(choice == 4)
        return 'W';
    else if(choice == 5)
        return 'V';
    else if(choice == 6)
        return 'U';
    else if(choice == 7)
        return 'T';
    else if(choice == 8)
        return 'S';
    else if(choice == 9)
        return 'R';
    else if(choice == 10)
        return 'Q';
    else if(choice == 11)
        return 'P';
    else if(choice == 12)
        return 'O';
    else if(choice == 13)
        return 'N';
    else if(choice == 14)
        return 'M';
    else if(choice == 15)
        return 'L';
    else if(choice == 16)
        return 'K';
    else if(choice == 17)
        return 'J';
    else if(choice == 18)
        return 'I';
    else if(choice == 19)
        return 'H';
    else if(choice == 20)
        return 'G';
    else if(choice == 21)
        return 'F';
    else if(choice == 22)
        return 'E';
    else if(choice == 23)
        return 'D';
    else if(choice == 24)
        return 'C';
    else if(choice == 25)
        return 'B';
    else if(choice == 26)
        return 'A';
    
    return 0;
}

// Used to take in a number and give a random number
// The purpose of this function is to return a random integer based off the integer passed in.
// Very simple function to generate a random number and place it in the memory location of 
// randNum. In this case it will always be 27 or CHAR_COUNT, to calculable the random number 
// because that's the number of chars to chose from.
static void get_rand_int(int *r)
{   
    static int hold = 0;	 // Used to seed the random function. 
    if (!hold)
    {
        srand(time(NULL));
        hold ++;
    }
	
    // The actual random number generated here. 
    *r = rand() % CHAR_COUNT;
}


///###############################################################################################
///####################################### MAIN FUNCTION  ######################################
///###############################################################################################
// Description: This program is pretty simple. It will create a random integer and then via
// 				a for-loop it will place that random numbers corresponding char into the newKey via
//				pickAChar function.	Finally the data is sent out via printf.
// Why:			I need a solution to creating a random key. So I took the two major factors I needed
//				I took random numbers and a list of chars. From there it was an easy forloop to
//				cycle through and create the list.
int main(int argc, char *argv[])
{
    //Source: http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
    unsigned char newKey[atoi(argv[1])]; 		// Used to create an array to the size that is passed in
    int randNum;
    
    // Used to randomly assign chars
    for (int i = 0; i < atoi(argv[1]); i++)
    {
        get_rand_int(&randNum);
        newKey[i] = pickAChar(randNum);
    }
    
    newKey[atoi(argv[1])] = '\0';
    
    // Used to output the data
    printf("%s\n", newKey);
    sleep(1);	// Used to fix random errors from grading script
    return 0;
}




























