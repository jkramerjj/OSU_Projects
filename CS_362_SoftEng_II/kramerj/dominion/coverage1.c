Joseph Kramer
CS362 Summer 2015
Assignment 3
Coverage1.txt


Unit Test 1: shuffle Function

File: 'dominion.c'
Lines executed: 15.69% of 580
Branches executed: 15.83% of 417
Taken at least once: 13.19% of 417
Calls executed: 7.37% of 95

File: 'unittest1.c'
Lines executed: 85.71% of 35
Branches executed: 100% of 8
Taken at least once: 50.00% of 8
Calls executed: 76.47% of 17

Overall a fairly thorough test. The test ran all parts of the shuffle function in the 
dominion.c file. Every branch of unittest1 ran, which equates to only 15.83% of the 
entire dominion.c file. I think it would be possible to get the dominion score higher if
I call another function that calls shuffle. Finally the function was called 16 times and 
had 100% returns, plus 95% blocks executed.  The only piece of code not used was the 
return of -1. To improve the code I could write a test that fails in such a way to call 
that piece of code.


 
Unit Test 2: isGameOver Function

File: 'dominion.c'
Lines executed: 17.41% of 580
Branches executed: 17.75% of 417
Taken at least once: 15.11% of 417
Calls executed: 7.37% of 95

File: 'unittest2.c'
Lines executed: 75.00% of 40
Branches executed: 81.82% of 22
Taken at least once: 59.09% of 22
Calls executed: 72.77% of 18

The test ran all parts of the isGameOver function in the dominion.c file. However the 
instance where j>=3 was only taken once. I think next time I would have that line of 
coded executed more, because its importance to the game. I think again here I could 
improve the test, if I wanted to test another function that calls isGameOver for the 
purpose of testing isGameOver through another function to see how it reacts. However, 
the isGameOver function on its own was test at every line of code. The branch coverage 
for the unittest wasn't at 100%, so I think I could redesign that to take every branch 
even if I think there is no point, maybe it will still find a bug. Finally the function 
is called 34 times and has 100% returns and 100% blocks executed.



Unit Test 3: getCost Function

File 'dominion.c'
Lines executed:22.41% of 580
Branches executed:24.46% of 417
Taken at least once:21.58% of 417
Calls executed:7.37% of 95

File: 'unittest3.c'
Lines executed: 85.00% of 20
Branches executed: 100.00% of 6
Taken at least once: 66.67% of 6
Calls executed: 75.00% of 8

This test was simple in nature. I hard coded in every card name and correct cost and then 
compared it to what’s in dominion.c The code ran and compared everything as expected. 
At this point I know the function works and returns the correct values. Any other 
function that calls can expect to get the correct value. The % of lines executed is higher
for doimnion.c because this test called more lines, however the lines were more trivial 
because they only returned one number: the cost. The function itself had been called 27 
times and had 100% returns, plus blocks executed of 97%. The only section of code missing 
was the return of -1, indicating that nothing was found. To improve the test, I could
write code that test for the -1 return.



Unit Test 4: supplyCount Function

File 'dominion.c'
Lines executed:22.76% of 580
Branches executed:24.46% of 417
Taken at least once:21.58% of 417
Calls executed:7.37% of 95

File: 'unittest4.c'
Lines executed: 85.00% of 35
Branches executed: 100.00% of 14
Taken at least once: 71.43% of 14
Calls executed: 76.47% of 17

This test had excellent branch coverage of 100% in unittest4.c and it executed every line
in the supplyCount function in dominion.c  Once again, a way to improve the overall test
would be to call the function form another function, but at this point it is returning
the correct numbers. The function was called 64 times and 100% returns, with 100% blocks 
executed, which indicates good coverage.



Card Test 1: Smithy Card

File 'dominion.c'
Lines executed:25.52% of 580
Branches executed:26.38% of 417
Taken at least once:22.78% of 417
Calls executed:9.47% of 95

File: 'cardtest1.c'
Lines executed: 93.33% of 30
Branches executed: 100.00% of 8
Taken at least once: 75.00% of 8
Calls executed: 77.78% of 9

This test ran every line of code in the smith function, but it only ran it a few times. 
I'm overall excited about that, I think I could have designed the test better with some 
forloops, basically use brute force to check it more. The card test file executed every 
branch and the lines executed are higher, because the test is more concise.  The smithy
function had 100% returns and 100% blocks executed, plus called 4 times.



Card Test 2: Adventurer Card

File 'dominion.c'
Lines executed:28.28% of 580
Branches executed:29.26% of 417
Taken at least once:24.94% of 417
Calls executed:10.53% of 95

File: 'cardtest2.c'
Lines executed: 89.47% of 38
Branches executed: 100.00% of 14
Taken at least once: 71.43% of 14
Calls executed: 71.43% of 14

This test did not run every line of code in the adventurer function. Once big miss was 
the deck count was never bellow zero, therefore the code to reshuffle was never called. 
I would need to redesign the test to either force hand count to 0 or run the test enough 
time where it happens naturally. The lines of execution were still respectable for 
even missing one section for the adventurer code. I think brute force may be a win to 
better this test.  In dominion.c the function had 3 returns at 100% blocks and executed 
93%, missing the shuffle. The function was called 6 times.



Card Test 3: Village Card 

File 'dominion.c'
Lines executed:29.14% of 580
Branches executed:29.26% of 417
Taken at least once:24.94% of 417
Calls executed:12.63% of 95

File: 'cardtest3.c'
Lines executed: 93.75% of 32
Branches executed: 100.00% of 8
Taken at least once: 75.00% of 8
Calls executed: 77.78% of 9

This code indicates respectable % for testing. 29.14% lines executed in dominion.c and 
93.75% for cardtest3.c, however I noticed the actual card function in dominion.c was only 
called twice. Which makes sense because I have the forloop let on the number of players 
and the number of players is 2. The theme I'm seeing here is that a little more brute 
force can go a long way in testing and I think I should have done that here to get my 
time spent in the Village Card function higher. Every line of code in village card was 
tested and almost of all in cardtest3.c, there isn't a way to get to 100%, because the 
logic is designed to choose one path if it failed and other if it succeeded. There was 
100% and 100% executing, plus 2 calls on the test code.



Card Test 4: Council Room Card 

File 'dominion.c'
Lines executed:31.72% of 580
Branches executed:31.18% of 417
Taken at least once:27.34% of 417
Calls executed:15.79% of 95

File: 'cardtest4.c'
Lines executed: 77.50% of 80
Branches executed: 76.67% of 60
Taken at least once: 46.67% of 60
Calls executed: 60.00% of 20

This cardtest4 test code did recieve 100% returns and 100% blocks executed, plus was 
called 4 times. The lines executed for cardtest4 are less than usual, but the code is 
based of many if statements so it is a reasonable number. The Council Room function in 
doinion.c was covered thoroughly, however with some brute force it could have been 
covered even more. From simply analyzing the logic of the function, I don't think brute 
for would of given different results. They way the bug is structured it will only be 
player1 that has an issue.




** Final Thoughts **
I think I can see the power of random testing in all of this. I know there were 
situations where I thought about implementing something like that, because I thought it 
would give better coverage. There is also the use of brute Force. I began to see how 
using to more computer power may be able to make the code break, because calling 
functions code 2-4 times just isn't enough.  I also learned how trivial bugs can be hard 
to catch and knowing the code your testing can be challenge on its own.














































