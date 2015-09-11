# CS372 Project #2
# Programmer: Joe Kramer
# Sources:	https://docs.python.org/2/library/socket.html
#			http://www.binarytides.com/python-socket-programming-tutorial/
# 			http://stackoverflow.com/questions/82831/check-whether-a-file-exists-using-python
#			http://stackoverflow.com/questions/6797984/how-to-convert-string-to-lowercase-in-python			


import socket
import time
import os.path
import getopt
import sys


# Used to verify if the user entered in all the correct info to operate 
# the program correctly. 
def initCommandCheck():
	if len(sys.argv) < 5:
		print "** Error ** Please type: 127.0.0.1 <control port> <-g/-l> [file name] <dataPort>\n"
		sys.exit()
	
	if sys.argv[3] == "-g" and len(sys.argv) != 6:
		print "** Error ** Please include a file name when using -g."
		print "	i.e. 127.0.0.1 <control port> <-g> [file name] <dataPort>\n"
		sys.exit()

	
	# Extra Credit Implementation ##
	# Sources:	http://stackoverflow.com/questions/82831/check-whether-a-file-exists-using-python
	#			http://stackoverflow.com/questions/6797984/how-to-convert-string-to-lowercase-in-python				
	if len(sys.argv) == 6:
		if os.path.isfile(sys.argv[4]):		
			print "\nFile already exists! "
			sys.stdout.write('Would you like to overwrite it? (Yes or No)--> ')
			decision = raw_input("")
			
			while 1:
				if decision.lower() == "yes" or decision.lower() == "y":				
					print "Accepted: File will be overwritten"
					break
				elif decision.lower() == "no" or decision.lower() == "n":
					print "Accepted: File will NOT be overwritten"
					print "Exiting program..."
					sys.exit()
				else:
					sys.stdout.write('Please enter either (Yes or No)--> ')				
					decision = raw_input("")
				
	
		
# Used to create the initial command socket
# Sources:	https://docs.python.org/2/library/socket.html
# 			http://www.binarytides.com/python-socket-programming-tutorial/	 	
def initiateContact():
	print "\nContacting server..."
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((sys.argv[1], int(sys.argv[2])))
	return s
		

# Used to send the data port number and list command to the server	
# Sources:	https://docs.python.org/2/library/socket.html
# 			http://www.binarytides.com/python-socket-programming-tutorial/	 		
def processListCommand(commandSocket):	
	print "Connected to server!"
	print "Sending ** LIST ** command to server"

	commandSocket.send(sys.argv[4]) # send datasocket
	commandSocket.send("-l")
	
# Used to send the data port number and get command to the sever
# Sources:	https://docs.python.org/2/library/socket.html
# 			http://www.binarytides.com/python-socket-programming-tutorial/	 	
def processGetCommand(commandSocket):	
	print "Connected to server!"
	print "Sending ** GET ** command to server"

	commandSocket.send(sys.argv[5]) # send datasocket
	commandSocket.send("-g")
	time.sleep(.2)  # I placed a time delay because of a crazy sending error, that this seemed to fix
	commandSocket.send(sys.argv[4])  


# This is the "guts" of the FTP program. 
# From here the initial command socket and data socket are made
# The functions that handle list and get are called from here 
# The sockets are closed
# Sources:	https://docs.python.org/2/library/socket.html
# 			http://www.binarytides.com/python-socket-programming-tutorial/	 	
def ftp_Program():		

	commandSocket = initiateContact()
	
	if sys.argv[3] == "-l":
		processListCommand(commandSocket)
		
	elif sys.argv[3] == "-g":
		processGetCommand(commandSocket)	
	
	dataSocket = connectDataSocket()
	commandSocket.close()
	dataSocket.close()
	print "Sockets closed. Program terminating...\n"


# Used to connect to the dataSocket that the user has chosen. 
# It is designed to receive list data as well as file data from the server. 
# http://stackoverflow.com/questions/19246103/socket-errorerrno-99-cannot-assign-requested-address-and-namespace-in-python
# https://docs.python.org/2/library/socket.html
def connectDataSocket():
	dataSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	if sys.argv[3] == "-l":
		dataSocket.bind(('', int(sys.argv[4])))
	else:
		dataSocket.bind(('', int(sys.argv[5])))
		
	dataSocket.listen(50)	
	cmndSocket1, cmndSocket2 = dataSocket.accept()	
	buffer = cmndSocket1.recv(15001)
	errorCheck = "** ERROR ** File does not exist\n"
	
	if sys.argv[3] == "-l":
		print "List Data--> " + buffer		   

	if buffer == errorCheck:
		print "** FILE \"" + sys.argv[4].upper() + "\" NOT FOUND ** Check spelling and try again!\n"
		sys.exit()
	
	# Discovered writing to file in python from 
	# Source: https://docs.python.org/2/tutorial/inputoutput.html
	if sys.argv[3] == "-g":
		print "Receiving file: " + sys.argv[5]
		with open(sys.argv[4], 'w') as newFile:
			newFile.write(buffer)
	return dataSocket   

	
if __name__ == '__main__':
	initCommandCheck()
	ftp_Program()



































































