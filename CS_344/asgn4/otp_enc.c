#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#define MAX_SIZE 2048

///###############################################################################################
///####################################### MAIN FUNCTION  ######################################
///###############################################################################################
// Description: This main function is designed to first declare needed variables and copy over the 
//				passed in arguments, in-order to move the logic along. Then a connection is 
//				facilitated and then error checked in-case it could not find the port.
//				If there is an error it will exit with a 2 as per the assignment. From there 
//				it reads-in in plainTextFile and keyGenFile and sends the information on out to 
//				get encoded.Finally depending on what is returned then print out the data. 
// Why:			This is done so that the encoding program can receive its needed info to work. After 
//				otp_enc_d is done the resulting ciphered info is received, because this way it will
//				follow the logic of the sequence of events. For example: I know I need to connect
//				to the server first to send and received data. 
	
int main(int argc, char *argv[]) 
{
	// Declare standard variables here
	int sockfd;							// Used for connecting	
	int	portNumber;						// Used for connecting	
    struct sockaddr_in server_address;	// Used for connecting	
    char buffer[MAX_SIZE];				// Used as a holder
	char plainTextFile[MAX_SIZE];		// Used to hold the sent in plaintext data
	char keyGenFile[MAX_SIZE];			// Used to hold the sent in keyGen data
	
	// Used to copy over argument values
	strcpy(plainTextFile, argv[1]);
    strcpy(keyGenFile, argv[2]);
    portNumber = atoi(argv[3]);	

	// Used to facilitate connection to the server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);    
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portNumber);
    int n = connect(sockfd,(struct sockaddr *) &server_address, sizeof(server_address)); 
	if(n < 0)
	{
        printf("** ERROR ** otp_enc could not find otp_enc_d.\n", portNumber);
        exit(2);
    }
	// Used to send the KeyGenFile
    snprintf(buffer, MAX_SIZE, "%s", keyGenFile);
    write(sockfd, buffer, strlen(buffer));
	
	// Used to send the PlainTextFle 
    memset(buffer, 0, MAX_SIZE);
    snprintf(buffer, MAX_SIZE, "%s", plainTextFile);
	write(sockfd, buffer, strlen(buffer));
	
	// Used to receive data from the server. 
    memset(buffer, 0, MAX_SIZE);
	read(sockfd, buffer, MAX_SIZE);     

	// If response received then print out buffer.
	if(buffer)
	{
		printf("%s\n", buffer);
		memset(buffer, 0, MAX_SIZE); // Used to reset buffer, which fixed word count issues from gradingscript		
	}
	
    close(sockfd);
     
    return 0;
}









































