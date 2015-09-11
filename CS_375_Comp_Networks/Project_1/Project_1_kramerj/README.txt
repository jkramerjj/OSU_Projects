Joseph Kramer
Project 1
CS372 Computer Networks
07-26-15


HOW TO COMPILE PROGRAM:
g++ chatserver.cpp -o chatserver

HOW TO RUN PROGRAM ON DIFFERENT TERMINALS:

ON CHATSERVER TERMINAL:
Type--> "hostname -i" and remember IP Address
	chatserver <portNumber> 
	i.e. hostname -i  
	i.e. chatserver 42000
		
ON CHATCLIENT TERMINAL:	
Type--> python chatclient.py <"hostname -i" found IP> <portNumber>
	i.e. python chatclient.py 128.193.54.7 42000
					


HOW TO RUN PROGRAM ON DUPLICATE TERMINALS:
ON DUPLICATE TERMINAL 1:
Type--> chatserver <portNumber> 
	i.e. chatserver 42000
		
ON DUPLCIATE TERMINAL 2:	
Type--> python chatclient.py 127.0.0.1 <portNumber>
	i.e. python chatclient.py 127.0.0.1 42000



	
If using separate terminals, I recommend using "hostname -i" to get the actual IP Address. 
Basically whatever shell the chatserver program  is using, type "hostname -i" into that 
terminal to get the actual IP Address. Then use that IP Address in the chatclient.py 
command line, which is running on a separate terminal.   

The program is designed for the chatclient to begin the communication and from there it 
ALTERNATES between the chatserver and the chatclient sending messages back and forth. 
For example once a message is sent via the chatclient, only the chatserver can respond, 
and when the chatserver responds then the chatclient can respond back. 

All testing was done on: flip.engr.oregonstate.edu

The server is hard coded with the name: jkramerj

Also when the chatclient is loaded, it will ask for a UserName. It will then use that 
name for the entire chat session. From there enter your message and press "ENTER."
The message will display on the terminal running chatserver.cpp, at that point enter
in the return message and press "ENTER." Rinse and repeat this cycle until ready to 
end it. Then type \quit into either the chatclient or chatserver. With \quit the 
chatserver will listen() for another connection and the chatclient will terminate. 




#######  Mock Run-through of Program #######

## chatserver.cpp terminal: ##
hostname -i
128.193.54.7
chatserver 42000
TestUser> Hello All
Kramerj> Bye Bye
Connection Ended. Good Bye


## chatclient.py terminal: ##
python chatclient.py 128.193.54.7 42000
Please enter a User Name: TestUser
TestUser> Hello All
Kramerj> Bye Bye
TestUser> \quit
Program Ended. Good Bye




** Remember to alternate between sending and receiving, the program IS NOT designed for 
the chatclient or chatserver to send more then one message at a time. ***

** Finally remember to type "hostname -i" in the chatserver terminal window to get that 
machines local IP ADDRESS ** 






































