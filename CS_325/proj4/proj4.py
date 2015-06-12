#!/usr/bin/python


import sys
import os
import math
import getopt
import time

TIMEOUT_SECS = 300

def usage(err=""):
	if (err != ""):
		print "Error:", err
	print "Usage:"
	print "  python", os.path.basename(__file__), "[-t] input_file"
	print "  -t     Find running time of algorithm (timeout at 5 mins)"
	print "           Timing info is output to \"input_file.time\""
	print "  -h     Display this message"
	print
	print "  input_file is a file of any number of lines where each line"
	print "    contains 3 integer numbers: unique city identifier,"
	print "    x-coordinate of city in x-y plane, and y-coordinate"
	print "    of city in x-y plane"
	print
	print "  Program outputs a file containing the tour length, followed by each"
	print "    city visited on separate lines. File name is <input_file>.tour"
	sys.exit()

# rounds up if decimal >= .5, down otherwise
def closest_int(x):
	if (x - int(x)) < .5:
		return int(x)
	else:
		return int(x) + 1

# calculates distance between 2 cities with pythagorean theorem
def city_distance(loc1, loc2):
	dist1 = (loc1[0]-loc2[0])**2
	dist2 = (loc1[1]-loc2[1])**2
	flt_dist = math.sqrt(dist1 + dist2)
	return closest_int(flt_dist)

# find tour for starting city
def calc_path(cities, start):
	# initialize everything, process start city
	not_visited = [city for city in cities]
	tour = []
	total_distance = 0
	not_visited.remove(start)
	tour.append(start)
	current_city = start

	# go while there are still cities to visit
	while not_visited != []:
		closest = (0, float("inf")) # big number, has to be a tuple
		# find the closest city from the current of the unvisited
		for city in not_visited:
			distance = city_distance(cities[current_city], cities[city])
			if distance < closest[1]:
				closest = (city, distance)
		# handle the found closest city
		tour.append(closest[0])
		not_visited.remove(closest[0])
		current_city = closest[0]
		total_distance += closest[1]
	# finish the tour when the loop is finished
	total_distance += city_distance(cities[start], cities[closest[0]])
	return (tour, total_distance)

def main(argc, argv):
	# process command line stuff
	if (argc < 2):
		usage("No arguments given")

	try:
		cl_opts, cl_args = getopt.getopt(argv[1:], "th")
	except getopt.error as inp_err:
		usage(str(inp_err))
	
	run_timings = False
	in_file = None
	for opt, arg in cl_opts:
		if (opt == "-t"):
			run_timings = True
		elif (opt == "-h"):
			usage()
		else:
			usage("Unable to process option "+str(opt))
	
	if (len(cl_args) != 1):
		usage("Invalid number of files specified")
	else:
		in_file = cl_args[0]
	
	# open input file
	input_fd = open(in_file, "r")

	# parse input file
	cities = {}
	for line in input_fd:
		# split on any whitespace
		temp = line.strip("\n\r").split()
		# add city to dictionary as {city: (x, y)}
		cities[int(temp[0])] = (int(temp[1]), int(temp[2]))
	input_fd.close()

	# start timing if necessary
	if (run_timings == True):
		start_time = time.time()
	
	# compute path starting at each city
	tours = []
	for city in cities:
		if (run_timings == True):
			# check timer
			if ((time.time() - start_time) >= TIMEOUT_SECS):
				print "Time of", (TIMEOUT_SECS / 60.0), "minutes has elapsed..."
				break
		ret = calc_path(cities, city)
		tours.append(ret)
	
	# get best tour
	shortest = (0, float("inf")) # big number, has to be a tuple
	for tour in tours:
		if tour[1] < shortest[1]:
			shortest = tour
	
	# stop timing and get total time if applicable
	if (run_timings == True):
		stop_time = time.time()
		total_time = stop_time - start_time
		timing_fd = open(in_file+".time", "w")
		timing_fd.writelines([str(total_time), " seconds"])
		timing_fd.close()

	# open output file
	output_fd = open(in_file+".tour", "w")
	output_fd.writelines([str(shortest[1]), "\n"])
	for city in shortest[0]:
		output_fd.writelines([str(city), "\n"])
	output_fd.close()


if __name__ == "__main__":
	main(len(sys.argv), sys.argv)
