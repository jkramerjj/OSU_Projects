#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_SIZE 2048

///###############################################################################################
///####################################### MAIN FUNCTION  ######################################
///###############################################################################################
// Description: This main function is designed to first declare needed variables and copy over the 
//				passed in arguments, in-order to move the logic along. Then a connection is 
//				facilitated and then error checked in-case it could not find the port.
//				If there is an error it will exit with a 2 as per the assignment. From there 
//				it reads-in in cipherTextFile and keyGenFile and sends the information on out to 
//				get decoded.Finally depending on what is returned then print out the data. 
// Why:			This is done so that the decoding program can receive its needed info to work. After 
//				otp_dec_d is done the resulting ciphered info is received, because this way it will
//				follow the logic of the sequence of events. For example: I know I need to connect
//				to the server first to send and received data. 
int main(int argc, char *argv[]) 
{
	// Declare standard variables here
    int sockfd;								// Used for connecting
	int	portNumber; 						// Used for connecting
    struct sockaddr_in server_address;		// Used for connecting
    char buffer[MAX_SIZE];					// Used as a holder. 
	char cipherTextFile[MAX_SIZE];			// Used to hold the sent in cipherText data
	char keyGenFile[MAX_SIZE];				// Used to hold the sent in keyGen data
	
	// Used to copy over argument values
	strcpy(cipherTextFile, argv[1]);
    strcpy(keyGenFile, argv[2]);
    portNumber = atoi(argv[3]);	
	
	// Used to create a client socket.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portNumber);
	//server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	
    int n = connect(sockfd,(struct sockaddr *) &server_address, sizeof(server_address));
	if(n < 0)
	{
        printf("** ERROR ** otp_dec could not find otp_dec_d.\n");
        exit(2);
    }

	// Used to send the keyGenFile
    snprintf(buffer, MAX_SIZE, "%s", keyGenFile);
    write(sockfd, buffer, strlen(buffer));
	
	// Used to send the cipherTextFile 
    memset(buffer, 0, MAX_SIZE);
    snprintf(buffer, MAX_SIZE, "%s", cipherTextFile);
    write(sockfd, buffer, strlen(buffer));  
 
	// This is used to receive the servers data. 
    memset(buffer, 0, MAX_SIZE);
    read(sockfd, buffer, MAX_SIZE); 

	// Display the buffer to screen or redirect to a file.
	if(buffer)
	{	
		printf("%s\n", buffer);		
	}
	close(sockfd);
	
    return 0;
}































