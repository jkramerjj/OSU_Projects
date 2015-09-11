Joseph Kramer
Project 2
CS372 Computer Networks
08-06-15


HOW TO COMPILE PROGRAM:
g++ ftserver.cpp -o ftserver

** Note ** This program was only ran and tested on flip local host: 127.0.0.1 

HOW TO RUN PROGRAM ON DUPLICATE TERMINALS:  ** Make sure same IP's on both Terminals **
ON DUPLICATE TERMINAL 1:
Type--> ftserver <portNumber> 
	i.e. ftserver 40000
		
ON DUPLCIATE TERMINAL 2:	
Type--> python ftclient.py 127.0.0.1 <portNumber> <-g/-l> [file name] <dataPortNumber> 
	i.e. python ftclient.py 127.0.0.1 40000 -g file.txt 40001



I had ftserver.cpp in a folder titled "server" and ftclient.py in a folder title "client." This was done to make transferring a file from one folder to another more apparent. Otherwise, if both programs were in the same folder, then the file transfer isn't as meaningful.

The program is designed for the ftserver to start first. Then ftclient will connect to the server. Ftserver will continue to run until a kill command is sent. Ftclient will terminate after every run. 

The file transferred from the server to the ftp client is: server.txt 
It contains: "This is server text more"


### EXTRA CREDIT ####
#1
I implemented--> if the ftclient sends a wrong file name to the ftserver, it will send back an error. (Which isn't extra credit, because I had to choose between ftserver or ftclientfile verification) 
But I also chose to implemented ftlcient verification (which was not required to implement both ftserver and ftclient file verification) While verifying ftclient files, if the file already exists, the ftclient program will ask the user if they'd like to overwrite the file or not.











#######  Mock Run-through of Program #######


## ftserver.cpp terminal: ##
mkdir server
mv ftserver.cpp ./server
g++ ftserver.cpp -o ftserver
ftserver 40000
** Waiting for FTP Client **
** File: server.txt selected ** Sending now...


## ftclient.py terminal: ##
mkdir client
mv ftclient.py ./client
python chatclient.py 128.193.54.7 40000  -g server.txt 40001
Contacting server...
Sending ** GET ** command to server on port 40001
Receiving file: server.txt
Sockets 40000 and 40001 closed. Program terminating...



** I placed ftserver and ftclient into their respective folders, this is not required, but it made transferring files more meaningful **


** Finally remember the program must be ran on duplicate terminals with identical IP addresses. *** 



