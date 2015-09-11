// CS372 Project #1
// Programmer: Joe Kramer
// Reference: http://beej.us/guide/bgnet/

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

//Globals
struct sockaddr_in hostAddress;
char serverHandle[510] = "Kramerj";	//Used as the server I.D.
char inBuffer[510];
char outBuffer[510];
int listenChat;
int portNumber;
int connectChat;
string clientsUserName;

// These boolians are used to handle when the client quits the connections but
// the sever still stays active while looking for another connection. 
bool incommingEndConnection;
bool outGoingEndConnection;
bool endConnection;

// Used to process the users chosen user name. 
void incomingUserName()
{
	memset(&inBuffer, 0, sizeof(inBuffer));
	recv(connectChat, inBuffer, 500, 0);
	clientsUserName = inBuffer;
	//cout << "Here is the client's user name ==" << clientsUserName << endl;
}


// Used to actually create a socket. This function is the initialization piece.
void creatNewSocket()
{
	//cout << "in creatNewSocket" << endl;	
	listenChat = socket(AF_INET, SOCK_STREAM, 0);
	memset(&hostAddress, '0', sizeof(hostAddress));
	hostAddress.sin_family = AF_INET;
	hostAddress.sin_port = htons(portNumber);
	hostAddress.sin_addr.s_addr = htonl(INADDR_ANY);
}


// This function is used to send chat info to the conencted client. 
void outGoingChat()
{
	cout << clientsUserName << "> " << inBuffer << endl;
	cout << serverHandle << "> ";
	cin.getline(outBuffer, 500);	
	
	string easyComparisonString = outBuffer;
	//cout << "From outGoingChat function, string == " << easyComparisonString << endl;	
	
	// used to verify string length is over 500
	while(easyComparisonString.length() > 500)
	{
		easyComparisonString.clear();
		cout << "Please enter a message of 500 characters or less" << endl;
		//cout << clientsUserName << "> " << inBuffer << endl;
		cout << serverHandle << "> ";
		cin.getline(outBuffer, 500);		
		easyComparisonString = outBuffer;
	}

	// If user would like to quit then quit the program.
	if (easyComparisonString == "\\quit")
	{
		cout << "Connection Ended \nWaiting for new connection..." << endl << endl;
		outGoingEndConnection = true;
		endConnection = true;
	}
	
	// Used to send data to the client
	send(connectChat, outBuffer, strlen(outBuffer), 0);
}


// This function is used to read in information from the client program. 
void incomingChat()
{
	//cout << "Inside incomingChat" << endl;
	recv(connectChat, inBuffer, 500, 0);	
	string easyComparisonString = inBuffer;
	//cout << "this is a string == " << easyComparisonString << endl;	
	
	// If user would like to quit then quit the program.
	if (easyComparisonString == "\\quit")
	{
		cout << "Connection Ended. \nWaiting for new connection..." << endl << endl;
		incommingEndConnection = true;
		endConnection = true;
	}	
}


// Used to accept the incoming connection. It will then send back the server name: kramerj
void approveConenction()
{
	// Accept incoming requests. 
	while(1)
	{
		connectChat = accept(listenChat, (struct sockaddr*)NULL,NULL);
		cout << "Connection granted! Chatting function initialized." << endl;
		send(connectChat, serverHandle, strlen(serverHandle),0);
		incomingUserName(); // used to get users chosen user name	
		
		//Logic sentinels to manage if the client decided to quit or not.
		endConnection = false;
		incommingEndConnection = false;
		outGoingEndConnection = false;
		
		while(!endConnection)
		{
			//cout << "Inisde endConnection While Loop" << endl;
			// Used to reset the buffers. 
			memset(&outBuffer, 0, sizeof(outBuffer));
			memset(&inBuffer, 0, sizeof(inBuffer));

			incomingChat();
			
			if(incommingEndConnection)
			{
				//cout << "incommingEndConnection == true" << endl;
				close(connectChat);
				listen(listenChat, 10);
			}
			else				
				outGoingChat();

			if(outGoingEndConnection)
			{
				//cout << "outGoingEndConnection == true" << endl;
				close(connectChat);
				listen(listenChat, 10);
			}
		}
	}
}


// Used to handle kill signals from the user. 
void sigintHandler(int pram)
{
	char quitBuffer[500];
	quitBuffer[0]='\\';
	quitBuffer[1]='q';
	quitBuffer[2]='u';
	quitBuffer[3]='i';
	quitBuffer[4]='t';
	//quitBuffer[5]='s';
	
	
	
	cout << "\n ** Signal Received ** Server has shut down...\n" <<  endl;
	send(connectChat, quitBuffer, strlen(quitBuffer), 0);		//Used to send a quit command to the client, because the server has shut down.
	close(connectChat);
	exit(1);
}


// This function is ment to be as a guide function. It will call all the functions 
// to run the socket program. 
int main(int argc, char **argv) 
{	
	if(argc!=2)
	{
		cerr << "Error: Please type--> ./chatserver.cpp <port number> " << endl;
		exit(1);
	}
	
	signal(SIGINT, sigintHandler);
	portNumber = atoi(argv[1]); // places the port number in the var	
	creatNewSocket();
	bind(listenChat, (struct sockaddr*)&hostAddress, sizeof(hostAddress)); 
	listen(listenChat, 10);
	approveConenction();
	
	return 0;
}






























