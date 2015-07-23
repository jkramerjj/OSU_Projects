#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#define MAX_SIZE 2048
#define DEC_ENC_COUNT 27


// Used to take in a number and give a char back.
// The purpose of this function is to return a character value for whatever integer is passed in.
// Because the ability to take a ciphered number and replace it with its char value is important
// for encryption but also decryption.
char pickAChar(int choice)
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


// Used to convert characters to an integer
// This function is used to take a passed in char and to convert it to it's integer counterpart.
// All text/char files will pass through this to get converted. I did this way because I needed
// a way to convert these chars into numbers, and simply listing on the chars and their corresponding
// was the most logically way to do it.
int convertToInteger(unsigned char choice)
{
    
    if (choice == ' ')
        return 0;
    else if(choice == 'Z')
        return 1;
    else if(choice == 'Y')
        return 2;
    else if(choice == 'X')
        return 3;
    else if(choice == 'W')
        return 4;
    else if(choice == 'V')
        return 5;
    else if(choice == 'U')
        return 6;
    else if(choice == 'T')
        return 7;
    else if(choice == 'S')
        return 8;
    else if(choice == 'R')
        return 9;
    else if(choice == 'Q')
        return 10;
    else if(choice == 'P')
        return 11;
    else if(choice == 'O')
        return 12;
    else if(choice == 'N')
        return 13;
    else if(choice == 'M')
        return 14;
    else if(choice == 'L')
        return 15;
    else if(choice == 'K')
        return 16;
    else if(choice == 'J')
        return 17;
    else if(choice == 'I')
        return 18;
    else if(choice == 'H')
        return 19;
    else if(choice == 'G')
        return 20;
    else if(choice == 'F')
        return 21;
    else if(choice == 'E')
        return 22;
    else if(choice == 'D')
        return 23;
    else if(choice == 'C')
        return 24;
    else if(choice == 'B')
        return 25;
    else if(choice == 'A')
        return 26;
      
    return 0;
}


///###############################################################################################
///####################################### MAIN FUNCTION  ######################################
///###############################################################################################
// Description: This function will operate as the decoding server. It is designed to read in the
// 				passed in data and then decode it. After connecting the program will jump into a
//				loop to act as a server to process data. To decode the data it will engage the
//				convertToInteger and pickAChar functions.   Then it will send the newly transformed
//				data out.
// Why:			I needed a way to always have this program ready to receive data. Therefore writing
//				it in a loop made sense. To process the decoding I simply just listed out all
//				the char and integers options in convertToInteger and pickAChar, then cycle through
//				choosing the one that works. This was the easiest way I could think of doing it.
//
int main(int argc, char *argv[])
{
    // Declare standard variables here
    int sockFD;								// Used for connecting
    int newSockFD;							// Used for connecting
    int portNumber; 						// Used for connecting
    socklen_t visiting_server_length; 				// Used for connecting
    char in_buffer[MAX_SIZE], out_buffer[MAX_SIZE]; 	// Used to facilitate transferring data
    struct sockaddr_in server_address, visiting_server; // Used for connecting
    char cipheredTextHolder[MAX_SIZE]; 		// Used to hold the sent in chiperedtext data
    char keyGenHolder[MAX_SIZE]; 			// Used to hold the sent in key gen data
    
    // Used for the process id
    pid_t cpid;
    
    // Used to fork from the parent process
    cpid = fork();
    
    // Used to initialize the daemon
    // Assign(bind) a server to a socket
    // and listen for a connection.
    sockFD = socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *) &server_address, sizeof(server_address));
    portNumber = atoi(argv[1]);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; // Used to accept any connections
    server_address.sin_port = htons(portNumber); // Used to listen for user entered port
    bind(sockFD, (struct sockaddr *) &server_address, sizeof(server_address)); 	// Assign to socket.
    listen(sockFD, 50);
    visiting_server_length = sizeof(visiting_server);
    FILE *fp;
    
    
    // This is used to act like the server. I used a loop, because servers are always accepting
    // connections; therefore this will infinite loop and always accept connections unless exited
    // within the loop.
    int alwaysLoop = 1;
    while (alwaysLoop)
    {
        // Used for connection attempts from a client
        newSockFD = accept(sockFD, (struct sockaddr *) &visiting_server, &visiting_server_length);
        
        // ##### START READ KEYGEN DATA #########
        memset(in_buffer, 0, MAX_SIZE);
        read(newSockFD, in_buffer, MAX_SIZE);
        
        // Used to open the sent file name
        fp = fopen(in_buffer, "r");
        
        // Used to store the key gen data
        fgets(keyGenHolder, MAX_SIZE, fp);
        fclose(fp);
        // ##### END READ KEYGEN DATA #########
        
        // ##### START READ CIPHEREDTEXT DATA #########
        memset(in_buffer, 0, MAX_SIZE);
        read(newSockFD, in_buffer, MAX_SIZE);
        
        // Used to open the sent file name an place the data into cipehredTextHolder
        fp = fopen(in_buffer, "r");
        fgets(cipheredTextHolder, MAX_SIZE, fp);
        fclose(fp);
        // ##### END READ CIPHEREDTEXT DATA #########
        
        // ##### DECRIPTION STARTS HERE ######
        // This is used to decrypt the data
        // First the cipheredTextHolder gets converted over to an integer value per character. i.e. A = 0755
        // Second the same thing happens for the keyGenHolder
        // Third the plainTextInteger is created by subtracting the 1st and 2nd step then if the sum is less
        // than zero then add 27. This is done so the cipheredTextHolder can actually have a character value
        // associated to it and the char values range from A-Z or 0-26 including the space.
        // Finally plainTextHolder is created
        
        // It is done this way because I needed a way to loop through the integer conversion switch statements and to
        // produce the decoded message. Since each char needs to have a corresponding integer, the only way I could
        // think of doing this was to list every integer / char option and then cycle through.
        
        // Variables needed for encryption
        unsigned long maxLength = strlen(cipheredTextHolder);
        char plainTextHolder[maxLength];
        // Arrays used to process the converted data
        int cipheredInteger[maxLength];
        int plainTextInteger[maxLength];
        int keyGenInteger[maxLength];
        
        for (int i = 0; i < maxLength; i++)
        {
            keyGenInteger[i] = convertToInteger(keyGenHolder[i]);
            cipheredInteger[i] = convertToInteger(cipheredTextHolder[i]);
            if(!(( plainTextInteger[i] = cipheredInteger[i] - keyGenInteger[i]) >= 0))
            {
                plainTextInteger[i] = (plainTextInteger[i] + DEC_ENC_COUNT);
            }
            plainTextHolder[i] = pickAChar(plainTextInteger[i]);
        }
        plainTextHolder[maxLength-1] = '\0';
        // ##### DECRIPTION ENDS HERE ######
        
        // This is used to write to screen or the output can be redirected via unix os.
        memset(out_buffer, 0, MAX_SIZE);
        snprintf(out_buffer, MAX_SIZE, "%s", plainTextHolder);
        write(newSockFD, out_buffer, strlen(out_buffer));
    }
    return 0;
}




































