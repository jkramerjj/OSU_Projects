Adventurer Card:
This random test focused on randomizing as much as possible. I randomized down to what 
cards are placed into the deck / hand. That means this tester randomly scatters copper,
silver, and gold through out the deck, along with the other card options. I did this to 
make it was close to a normal game as possible. The adventurer card is then placed in 
a random spot in the deck. That spot is saved for use when the adventurer function is
called. The program will then add up the total amount of treasure cards before the 
adventurer function is called, so it can be compared to the total number of treasure cards
after the function is called. And it's between those two numbers where I can find an 
error. Because everything is random, sometimes a deck is created with 0 or 1 treasure cards, 
I have the tester run functions that maintain at-least 2+ treasure cards in the deck and 
functions that don't check for treasure cards. 

The tester tests both the adventurer function and the playcard function which calls the 
adventurer function. I have it run 90,000 iterations, keeping track of successes and 
failures. I know from the previous assignment, that player1 can play through with out 
bugs, and that shows to be true with this test. 


Smithy Card:
I tried to randomly create all possible situations the Smithy card could be in. I did this 
by randomly generating hand-sizes and cards within the hand. I then had one Smithy card 
inserted into the hand so I knew where to use it. The program will then simply store
the number of cards before and after the function is called. Then it will compare the 
two values and if they're not equal it will register an error. 

This tester test both the smithy function and the smith function via the playCard function.
The test runs 90,000 times and has no succesfull returns. That is because the bug will
always return 1 extra card, whenever the function is called. I cannot think of any other
way to test this, that could change it form drawing 1 extra card. 


Coverage: 
The coverage of percentages of the random tester programs are fairly higher than the unittest scores.
Both tests search for the same bugs. It so happens that the random test, runs the test many
more times and has the possibility of finding something that a single test may not. 
However the random tests are using 100% of their chosen card funciton and 25-29% of 
the entire dominion.c program, which is understandable because I am only running sections 
of the code. However I still test for all cornre and edge cases. 
