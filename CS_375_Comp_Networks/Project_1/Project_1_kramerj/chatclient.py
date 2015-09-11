#CS372 Project #1
#Programmer: Joe Kramer
#Reference: https://docs.python.org/2/library/socket.html
#			http://www.tutorialspoint.com/python/python_networking.htm

# Needed imports
import socket
import getopt
import sys
import os


# Used to manage the messaging program. 
# Runs the whileloop that operates the client
def messagingClient():
	socket_holder = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	socket_holder.connect((ip_address, port_number))
	
	serverName = socket_holder.recv(500)	#Receives the servers name which is Kramerj
	
	# This block is used to get the users desired username. 
	sys.stdout.write('Please enter a User Name: ')		
	newUserName = raw_input("")
	#print len(newUserName)
	while len(newUserName) > 10:
		sys.stdout.write('Please re-enter a User Name of 10 characters or less: ')		
		newUserName = raw_input("")
	
	socket_holder.send(newUserName)
		
	while 1:
		outGoingBuffer(socket_holder, newUserName)
		in_buffer = str(socket_holder.recv(500))
		
		if in_buffer == "\quit":
			print "Program Ended. Good Bye"
			socket_holder.close()
			sys.exit()
		else:
			print serverName + "> " + in_buffer
		
		
# Used to process outgoing messages via send()
# also used to display the users chosen username		
def outGoingBuffer(socket_holder, newUserName):
	#print newUserName
	sys.stdout.write(newUserName)
	out_buffer = raw_input("> ")
	
	# Used to verify string length is over 500
	while (len(out_buffer) > 500):
		print "Please enter a message of 500 characters or less"
		sys.stdout.write(newUserName)
		out_buffer = raw_input("> ")
		
	socket_holder.send(out_buffer)
	if out_buffer == "\quit":
		print "Program Ended. Good Bye"
		socket_holder.close
		sys.exit()	
	

# used to check the command line arguments
# also used to call the messagingClient function, which runs the 
# the majority of the program. 	
if __name__ == '__main__':
	if len(sys.argv) != 3:
		print "Error: Please Enter --> python chatclient.py <IP Address> <Port Number>"
		sys.exit()
	
	ip_address = sys.argv[1]
	port_number = int(sys.argv[2])
	
	messagingClient();
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 