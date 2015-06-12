#!/usr/bin/env python

# Project 1 - Maximum Sum Subarray
# Jacob Branaugh, Jennifer Burns, Joseph Kramer

from __future__ import print_function
import sys
import os
import random
import time

################## Algorithm 1 ##################
def computeSum(numList, i, j):
	sum = 0
	for index in range(i, j+1):
		sum += numList[index]
	return sum

def findMaxSumAlg1(numList, numberFile, printResults=True):
	maxSum = 0
	foundI = 0
	foundJ = 0

	for i in range(0, len(numList)):
		for j in range(i, len(numList)):
			temp = computeSum(numList, i, j)
			if maxSum < temp:
				maxSum = temp
				foundI = i
				foundJ = j


	if printResults is True:
		if maxSum > 0:
			print(numList[foundI:(foundJ+1)], end=', ', file=numberFile)
		else:
			print("(empty)", end=', ', file=numberFile)
		print(maxSum, file=numberFile)
#################################################


################## Algorithm 2 ##################
def findMaxSumAlg2(numList, numberFile, printResults=True):
	maxSum = 0
	foundI = 0
	foundJ = 0

	for i in range(0, len(numList)):
		iSubSum = 0
		for j in range(i, len(numList)):
			iSubSum += numList[j]
			if maxSum < iSubSum:
				maxSum = iSubSum
				foundI = i
				foundJ = j


	if printResults is True:
		if maxSum > 0:
			print(numList[foundI:(foundJ+1)], end=', ', file=numberFile)
		else:
			print("(empty)", end=', ', file=numberFile)
		print(maxSum, file=numberFile)
#################################################


################## Algorithm 3 ##################
REALLY_SMALL_NUMBER = -10000

def max_of_two(a, b):
	if a > b:
		ret = a
	else:
		ret = b
	return ret

def max_of_three(a, b, c):
	temp = max_of_two(a, b)
	return max_of_two(temp, c)

def max_sum_crossing_mid(array, min_idx, mid_idx, max_idx):
	#left side
	temp_sum = 0
	left_sum = REALLY_SMALL_NUMBER #initialize lower than lowest number in array
	for i in range(mid_idx, min_idx - 1, -1): #i from mid down to min inclusive
		temp_sum += array[i]
		if (temp_sum > left_sum):
			left_sum = temp_sum
			foundStart = i
	
	#right side
	temp_sum = 0
	right_sum = REALLY_SMALL_NUMBER
	for i in range(mid_idx + 1, max_idx + 1): #i from mid+1 up to max inclusive
		temp_sum += array[i]
		if (temp_sum > right_sum):
			right_sum = temp_sum
			foundEnd = i
	
	return left_sum + right_sum, foundStart, foundEnd

def max_sum_alg3(array, min_idx, max_idx):
	if min_idx == max_idx:
		foundEnd = min_idx
		foundStart = min_idx
		return array[min_idx], foundStart, foundEnd
	
	mid_idx = (min_idx + max_idx) / 2

	return max_of_three(max_sum_alg3(array, min_idx, mid_idx),
	                    max_sum_alg3(array, mid_idx + 1, max_idx),
	                    max_sum_crossing_mid(array, min_idx, mid_idx, max_idx))

def findMaxSumAlg3(numList, numberFile, printResults=True):
	numList_len = len(numList)
	maxSum, foundStart, foundEnd = max_sum_alg3(numList, 0, numList_len - 1)

	if printResults is True:
		if maxSum > 0:
			print(numList[foundStart:(foundEnd+1)], end=', ', file=numberFile)
		else:
			print("(empty)", end=', ', file=numberFile)
		print(maxSum, file=numberFile)
#################################################


################## Algorithm 4 ##################
def findMaxSumAlg4(numList, numberFile, printResults=True):
	maxEndingHere = maxSoFar = 0
	foundStart = currentIndex = foundEnd = 0
	for i in range(0, len(numList)):
		maxEndingHere = max(0, maxEndingHere + numList[i])
		if maxEndingHere == numList[i]:
			currentIndex = i
		maxSoFar = max(maxSoFar, maxEndingHere)
		if maxSoFar == maxEndingHere:
			foundStart = currentIndex
			foundEnd = i


	if printResults is True:
		if maxSoFar > 0:
			print(numList[foundStart:foundEnd+1], end=', ', file=numberFile)
		else:
			print("(empty)", end=', ', file=numberFile)
		print(maxSoFar, file=numberFile)
#################################################


# The print functions of this code are turned off as the data for these timings has already been collected
def getTimings(algToTest):
	sizeList = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]
	timingsFile = "timingResultsMSSAlg" + str(algToTest) + ".txt"
	writeFile = open(timingsFile, 'w')

	for size in sizeList:
		iteration = 1
		timeSum = 0
		while iteration <= 10:
			i = 0
			numList = []

			while i < size:
				numList.append(random.randint(-99, 99))
				i += 1

			# Test algorithms
			if algToTest == 1:
				start = time.clock()
				findMaxSumAlg1(numList, None, False)
				end = time.clock()
				timing = 0.000 + end - start
				if iteration == 10:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, " Time: ", timing, file=writeFile)
				else:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, "  Time: ", timing, file=writeFile)

			elif algToTest == 2:
				start = time.clock()
				findMaxSumAlg2(numList, None, False)
				end = time.clock()
				timing = 0.000 + end - start
				if iteration == 10:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, " Time: ", timing, file=writeFile)
				else:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, "  Time: ", timing, file=writeFile)

			elif algToTest == 3:
				start = time.clock()
				findMaxSumAlg3(numList, None, False)
				end = time.clock()
				timing = 0.000 + end - start
				if iteration == 10:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, " Time: ", timing, file=writeFile)
				else:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, "  Time: ", timing, file=writeFile)

			elif algToTest == 4:
				start = time.clock()
				findMaxSumAlg4(numList, None, False)
				end = time.clock()
				timing = 0.000 + end - start
				if iteration == 10:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, " Time: ", timing, file=writeFile)
				else:
					print("Algorithm ", algToTest, "- Size: ", size, "  Iteration: ", iteration, "  Time: ", timing, file=writeFile)

			timeSum += end - start
			iteration += 1

		average = timeSum / (iteration - 1)
		print("Average Time: ", average, file=writeFile)

def getTargetFile(fileName, whichAlg):
	index = fileName.index('.')
	targetFile = fileName[:index]
	targetFile = targetFile + "_results" + whichAlg + ".txt"
	return targetFile

def main():
	if len(sys.argv) >= 3:
		if sys.argv[1] == '-f' and len(sys.argv) >= 4:
			numberFile = open(sys.argv[2], 'r')
			fileLines = numberFile.readlines()
			targetFile = getTargetFile(sys.argv[2], sys.argv[3])
			writeFile = open(targetFile, 'w')

			for line in fileLines:
				stringList = line.strip('[]\n\r').split(',')
				try:
					numList = map(int, stringList)
				except:
					numList = map(float, stringList)
				if sys.argv[3] == '1':
					findMaxSumAlg1(numList, writeFile)
				elif sys.argv[3] == '2':
					findMaxSumAlg2(numList, writeFile)
				elif sys.argv[3] == '3':
					findMaxSumAlg3(numList, writeFile)
				elif sys.argv[3] == '4':
					findMaxSumAlg4(numList, writeFile)

			numberFile.close()
			writeFile.close()

		elif sys.argv[1] == '-r':
			if len(sys.argv) >= 3:
				if sys.argv[2] == '1':
					getTimings(1)
				elif sys.argv[2] == '2':
					getTimings(2)
				elif sys.argv[2] == '3':
					getTimings(3)
				elif sys.argv[2] == '4':
					getTimings(4)

if __name__ == "__main__":
	main()
