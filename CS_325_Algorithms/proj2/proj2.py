#!/usr/bin/python
#
# Created by: Jacob Branaugh, Joseph Kramer
# Created on: 02/10/2015 13:49
#
# Program for cs325 project 2
#

import sys
import getopt
import os
import time

def usage(exitcode=1):
	print "Usage:"
	print "  python "+os.path.basename(__file__)+" [OPTIONS]\n"
	print "  -a ALG_NAME   specify algorithm to run (slow, greedy, dp)"
	print "  -f FILE.txt   specify file FILE containing input data"
	print "  -o            output results of algorithm to file if -f flag given"
	print "  -t DATA_SET   prints timing information for algorithm using predefined data (overrides -f -p -o)"
	print "                  DATA_SET must be 1 or 2"
	print "  -p            prints data written to output file to stdout"
	print "  -h            display this message"
	sys.exit(exitcode)

# Sources for Change_Slow Algorithm:
#       http://stackoverflow.com/questions/12520263/recursive-change-making-algorithms
#       https://www.youtube.com/watch?v=EScqJEEKC10
def change_slow(a, v, c):
	if(len(v) == 0):
		pass
	elif(sum(c) == a):
		yield c
	elif(sum(c) > a):
		pass
	else:
		for i in change_slow(a, v[:], c + [v[0]]):
			yield i
		for i in change_slow(a, v[1:], c):
			yield i


########### Slow Algorithm #####################################################
def run_slow(data, output_fd, print_output, print_timings):
	for item in data:
		coins = item[0]
		amount = item[1]
		printed_coins = coins
		if (print_timings == True):
			start_time = time.clock()

		coins_needed = [j for j in change_slow(amount, coins, [])]

		if (print_timings == True):
			end_time = time.clock()
			print "Slow algorithm for amount", amount, "ran in", end_time - start_time, "seconds"

		###############################################################
		###### The following code is used to display results as #######
		######  a value for each amount of currency needed: ###########
		###### Example: [10,10,10,10] = [0,4,0,0], meaning 4 tens #####
		###############################################################

		min_coins_needed = min(coins_needed, key=len)

		for even_out in range(len(coins)):
			if(len(coins)==len(min_coins_needed)):
				break
			elif(len(coins) < len(min_coins_needed)):
				break
			elif(coins[even_out] != min_coins_needed[even_out]):
				min_coins_needed.insert(even_out,0)

		for z in range(len(coins)):
			t = 0
			count = 0
			for t in range(len(min_coins_needed)):
				if(printed_coins[z] == min_coins_needed[t]):
					count +=1
			printed_coins[z]=count

		###############################################################
		################# End Specific Display Code ###################
		###############################################################


		if (print_output == True):
			print "Minimal Option",printed_coins  # results from running algorithm
			print "Number of Coins: ", sum(printed_coins)
		if (output_fd != False):
			output_fd.writelines([str(printed_coins).replace(" ",""), "\n"])
			output_fd.writelines([str(sum(printed_coins)), "\n"])

################################################################################

########### Greedy Algorithm ###################################################
def run_greedy(data, output_fd, print_output, print_timings):
	for item in data:
		coins = item[0]
		amount = item[1]

		# initialize solution array
		solution = []
		for i in range(0, len(coins)):
			solution.append(0)

		# get coins list sorted from largest to smallest
		coins_sorted = []
		for i in range(len(coins)-1, -1, -1):
			coins_sorted.append(coins[i])

		# start timing if applicable
		if (print_timings == True):
			start_time = time.time()

		# run algorithm
		temp = amount
		for coin in coins_sorted:
			while (coin <= temp):
				temp -= coin
				solution[coins.index(coin)] += 1

		# get number of coins from solution array
		num_coins = 0
		for count in solution:
			num_coins += count

		if (print_timings == True):
			end_time = time.time()
			print "Greedy algorithm for amount", amount, "ran in", end_time-start_time, "seconds"
		if (print_output == True):
			print "Coin values:  ", coins
			print "Count of each:", solution
			print "Total coins:  ", num_coins
		if (output_fd != False):
			output_fd.writelines([str(solution).replace(" ",""), "\n"])
			output_fd.writelines([str(num_coins), "\n"])
################################################################################

########### DP Algorithm #######################################################
def run_dp(data, output_fd, print_output, print_timings):
	for item in data:
		coins = item[0]
		amount = item[1]
		if (print_timings == True):
			start_time = time.time()

		numEach = [0] * (amount + 1)
		numEachArray = [0] * len(coins)
		minCoins = [None] * (amount + 1)
		minCoins[0] = 0

		for value in range(1, (amount + 1)):
			min = 10000
			for i in range(0, len(coins)):
				if coins[i] <= value:
					if (1 + minCoins[value - coins[i]]) < min:
						min = 1 + minCoins[value - coins[i]]
						first = i
			minCoins[value] = min
			numEach[value] = first

		numCoins = amount

		while amount > 0:
			numEachArray[numEach[amount]] = numEachArray[numEach[amount]] + 1
			amount = amount - coins[numEach[amount]]

		if (print_timings == True):
			end_time = time.time()
			print "DP algorithm for amount", amount, "ran in", end_time-start_time, "seconds"
		if (print_output == True):
			print numEachArray, minCoins[numCoins]
		if (output_fd != False):
			output_fd.writelines([str(numEachArray).replace(" ",""), "\n"])
			output_fd.writelines([str(minCoins[numCoins]), "\n"])

################################################################################

def main(argc, argv):
	# exit if no args specified
	if (argc == 0):
		usage()

	# get command line arguments
	try:
		cl_opts, cl_args = getopt.getopt( argv[1:], "f:ot:pa:h")
	except getopt.error as inp_err:
		print "ERROR: "+str(inp_err)
		usage()

	# set cl opt defaults
	input_file = False
	output_file = False
	print_output = False
	print_timings = False
	algorithm = False

	# process cl args
	for opt, arg in cl_opts:
		if (opt == "-f"):
			input_file = arg
		elif (opt == "-o"):
			output_file = True
		elif (opt == "-t"):
			try: # ensure argument is only 1 or 2
				timings_set = int(arg)
				if timings_set not in [1,2]:
					raise
			except:
				print "ERROR: Invalid argument", arg, "to option -t"
				usage()
			print_timings = True
		elif (opt == "-p"):
			print_output = True
		elif (opt == "-a"):
			algorithm = arg
		elif (opt == "-h"):
			usage()
		else:
			print "ERROR: Unable to process option "+str(opt)
			usage()
	
	# process command line options
	if (algorithm == False):
		print "ERROR: no algorithm given to run"
		usage()

	data = []
	if (print_timings == True):
		print_output = False
		output_fd = False
		if (timings_set == 1):
			for i in range(100, 900, 100):
				data.append(([1,10,25,50],i))
		elif (timings_set == 2):
			for i in range(100, 900, 100):
				data.append(([1,3,4,17,31],i))
		else:
			print "ERROR: Neither timings set is being used"
			usage()
	else: #not performing timing analysis
		if (output_file == False) and (print_output == False):
			print "ERROR: program will not output results anywhere"
			usage()
		if (input_file == False):
			print "ERROR: no input given"
			usage()

		# setup input file descriptor and parse data from file
		input_fd = open(input_file, "r")
		lines = []
		for line in input_fd.readlines():
			lines.append(line.strip("[]\n\r"))
		for i in range(0, len(lines), 2):
			data.append((map(int, lines[i].split(",")), int(lines[i+1])))
		input_fd.close()

		# open output file descriptor for writing
		if (output_file == True):
			idx = input_file.index(".")
			output_fd = open(input_file[:idx]+"_"+algorithm+"_results"+input_file[idx:], "w")
		else:
			output_fd = False

	# run algorithm
	if (algorithm == "slow"):
		run_slow(data, output_fd, print_output, print_timings)
	elif (algorithm == "greedy"):
		run_greedy(data, output_fd, print_output, print_timings)
	elif (algorithm == "dp"):
		run_dp(data, output_fd, print_output, print_timings)
	else:
		print "ERROR: algorithm", algorithm, "not available"
		usage()

	# try to close file descriptor, ignore if exception because program is done
	# anyway, exception probably means file descriptor wasn't created
	try:
		output_fd.close()
	except:
		pass

if __name__ == "__main__":
	main(len(sys.argv), sys.argv)
