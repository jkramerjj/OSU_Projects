// CS372 Project #2
// Programmer: Joe Kramer
// Sources:	http://beej.us/guide/bgnet/
//			http://www.linuxhowtos.org/C_C++/socket.htm
//			http://www.retran.com/beej/getpeernameman.html
// 			http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
//			http://pubs.opengroup.org/onlinepubs/007908775/xsh/dirent.h.html
//			http://www.cplusplus.com/forum/general/100714/

#include <signal.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>

using namespace std;

//Globals
int cnrtlPNum=0;
struct sockaddr_in hostAddress;
int controlSocket, dataSocket;
int initSocket=0;
int dataPort=0;
char incomingCommand[5];


// Used to reset incomingCommand
void reset(char *eraseMe)
{
	memset(eraseMe, 0, sizeof(eraseMe));
}


// This function is designed to connect to the dataport. 
// It will check for connection errors
// Sources: http://www.retran.com/beej/getpeernameman.html
//			http://beej.us/guide/bgnet/
int dataConnection() 
{
	struct sockaddr_in addrs;
	int connectChecker = -1;
	int ipChecker = 0;
	int dataCon;
	
	// Found out about getpeername from 
	// http://www.retran.com/beej/getpeernameman.html
	unsigned int addrsSize = sizeof(addrs);	
	ipChecker = getpeername(controlSocket, (struct sockaddr *) &addrs, &addrsSize);
	if(ipChecker == -1)
	{
		cout <<"** Error ** Unable to receive FTP Client's IP" << endl;
		close(controlSocket);
		exit(1);
	}
	
	// Used to connect to new dataport. 
	addrs.sin_port = htons(dataPort);
	
	// Used to create a new socket for the data to transfer over. 
	dataCon = socket(AF_INET, SOCK_STREAM, 0);
	if(dataCon == -1)
	{
		cout << "** Error ** Unable to create a socket "  << endl;
		exit(1);
	}

	// Used to connect to the FTP Client 
	while(connectChecker == -1)
	{
		connectChecker = connect(dataCon, (struct sockaddr *) &addrs, sizeof(addrs)); 
	}

	return dataCon;
}


// Used to get the dataport port number
int getDataport()
{
	reset(incomingCommand);
	recv(controlSocket, incomingCommand, sizeof(incomingCommand), 0);
	//cout << "dataPort == " << incomingCommand << endl;
	char temp[500];
	memcpy(temp, incomingCommand, sizeof(temp));
	int dp = atoi(temp);
	return dp;
}


// Used to validate command line data
void validate(int argc, char *argv)
{
	if(argc != 2)
	{
		cout << "\nPlease enter in a Port Number\ni.e. ./ftserver <port number>\n" << endl;
		exit(1);
	}
	
	// Validation of integer was sourced from:
	// http://stackoverflow.com/questions/19372145/checking-if-argvi-is-a-valid-integer-passing-arguments-in-main
	cnrtlPNum=atoi(argv);
	
	while(*argv)
	{
		if(!isdigit(*argv++))
		{
			cout << "Please enter only digits 0-9\ni.e. 40000" <<endl;
			exit(1);
		}
	}	
	//cout << "port number == " << cnrtlPNum << endl;	
}


// Used to handle all List commands sent over by the FTP Client
void processListCommand()
{
	// Found how to search directories from:
	// http://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
	// http://pubs.opengroup.org/onlinepubs/007908775/xsh/dirent.h.html
	string holder;
	DIR * dir;
	struct dirent * fname; 
	cout << "** List ** Selected. Sending now on dataport " << dataPort << " ... \n" << endl;
	dataSocket = dataConnection();
	
	//cout << "MADE IT HERE!!! " << endl;
	if((dir = opendir("./")) == NULL) 
	{
		cout << "** Error ** Unable to open the directory" << endl;
		exit(10);
	}
	//cout << "made it here!" <<endl;
	while((fname = readdir(dir)) != NULL) 
	{
		if((strcmp(fname->d_name, "..") != 0) && (strcmp(fname->d_name, ".") != 0)) 
		{		
			holder = fname->d_name;
			holder += " ";
			
			// Learned about char* and c_str() from:
			// Source: http://www.cplusplus.com/forum/general/100714/
			const char* buffer = holder.c_str();			
			//holder.clear();
			
			// Used to send the gathered list back to FTP client. 
			send(dataSocket, buffer, strlen(buffer), 0);
		}
	}
	reset(incomingCommand);
	close(controlSocket);
	close(dataSocket);
}


// Used to handle all Get commands sent over by the FTP Client
// Source: http://beej.us/guide/bgnet/
void processGetCommand()
{
	int passTest;
	char fileName[500];	 
	bool skipIt = false;
	memset(fileName, 0, sizeof(fileName));
	
	// Used to receive the file name.
	recv(controlSocket, fileName, sizeof(fileName), 0);	
	//cout << "FILENAME == " << fileName << endl;
	cout << "** File: " << fileName << " Selected ** Sending now on dataport " << dataPort << "...\n" << endl;
	
	// Used to get the data socket.
	dataSocket = dataConnection();	
		
	// Used to validate that the file was opened correctly
	// If not, then it will display error message and set skipIt to true. 
	passTest = open(fileName, O_RDONLY);
	if(passTest == -1)
	{
		// Learned about char* from
		// Source: http://www.cplusplus.com/forum/general/100714/	
		const char* errorMsg = "** ERROR ** File does not exist\n";	
		send(dataSocket, errorMsg, strlen(errorMsg), 0);
		close(dataSocket);
		cout << errorMsg << endl;
		skipIt = true;		
	}

	// Dropped down to C, because I've used this before in CS344 asgn4, where we had to 
	// encrypt files and then send them.
	// Source: http://www.linuxhowtos.org/C_C++/socket.htm
	if(skipIt == false)
	{
		FILE *fp;
		char out_buffer[1024];
		reset(out_buffer);
		fp = fopen(fileName, "r");
		fgets(out_buffer, 1024, fp); // copy data to buffer	
		//cout << "THE OUT_BUFFER == " << out_buffer << endl;
		write(dataSocket, out_buffer, strlen(out_buffer));			
		fclose(fp);
	}
	reset(incomingCommand);
	close(dataSocket);
}

// Used to handle kill signals from the user.
// This code is reused from Asgn1 
void sigintHandler(int pram)
{
	close(controlSocket);
	close(dataSocket);
	cout << "\n ** Signal Received ** Sockets " << cnrtlPNum << " and " << dataPort << " Closed and Server Shut Down.\n" <<  endl;	
	exit(1);
}

// This function is designed to create the socket and then listen. 
void initialSocket()
{
	//Here I used the same code from Asgn1 to set up a socket
	//It was originally sourced from: http://beej.us/guide/bgnet/output/html/multipage/index.html
	initSocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(&hostAddress, '0', sizeof(hostAddress));
	hostAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	hostAddress.sin_port = htons(cnrtlPNum);
	hostAddress.sin_family = AF_INET;
	
	bind(initSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress));
	
	cout << "** Waiting ** For FTP Client \n" << endl; 
	
	listen(initSocket, 10); 
}


// Used to process the communications between server and FTP client. 
// Sources: CS-344 Project 4 is VERY similar to this
// http://beej.us/guide/bgnet/
// http://www.linuxhowtos.org/C_C++/socket.htm
void processCommunications()
{	
	// Always reset incomingCommand for good measure
	reset(incomingCommand);
	
	while(1)
	{
		controlSocket = accept(initSocket,(struct sockaddr*) NULL, NULL);
		cout << "** Connection Established on port " << cnrtlPNum << " **" << endl;
		
		// Holds the passed in dataport from the FRP
		dataPort = getDataport();
		reset(incomingCommand);
		
		recv(controlSocket, incomingCommand, sizeof(incomingCommand), 0);
		//cout << "Command Entered == " << incomingCommand << endl;
		
			if(strcmp(incomingCommand, "-l") == 0)
			{			
				processListCommand();	
			}		
			else if(strcmp(incomingCommand, "-g") == 0)
			{		
				processGetCommand();			
			}		
		
		close(controlSocket);
		close(dataSocket);		
	}
}


// Used to handle the calling of the functions that run the program.
int main (int argc, char *argv[])
{	
	validate(argc, argv[1]);	// Used to validate user inputs
	signal(SIGINT, sigintHandler); //Used to process kill signals
	initialSocket();	// Initiate the socket command process
	processCommunications();	// Process the operations of a server 
	
	return 0;
}
























































