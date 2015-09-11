inputChar()
This function is designed so that each time it is called it will create a random 
number between 0 and 8. It will then return the char array with the random number used
to select the char within the array. 

example: return chArray[randNum]

*inputString()
This function is designed to create 6 random numbers that are not the same random number.
The computer ran so fast, that the rand function would randomly create 6 numbers that were
exactly the same. There for I had to create a forloop that guaranteed the numbres would 
not all be the same. The focuntion then it places the random numbers into the "reset" 
array to make a word. Finally it returns the results. 

Summary:

The program moved so fast that the random number generator wasn't seeding fast enough and 
it would display the same number for many iterations. I noticed with *inputSrings(), that
it would return works likes: eeeee or sssss. The problem was that the random number
generator wasn't working fast enough, so I created a while loop that would cycle
though each random number and check if that random number was generated for this 
particular function call. If it was then the while loop would continue to call the random
number generator until it gave 5 different random numbers. 

I initially had *inputString() try to randomly recreate "reset\0", which is 6 different
open places to put a letter. When I would run the program the OSU servers killed the
program at 19,450,204 iterations.  I know my logic was sound, but my malloc allocation was
too high and I was running out of memeory. When I lowered that I could run the itterations
for the worf "reset\0" 

In the end this was a fun quiz. I enjoyed pushing the CPU the most. 

To make the file please type: gcc -o testme testme.c -g
