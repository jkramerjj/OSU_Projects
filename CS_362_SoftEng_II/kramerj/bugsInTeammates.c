Joe Kramer
CS 362 Assignment #5
07-29-15

Teammate1Dominion -- Eric L
Platform: Linux flip2.engr.oregonstate.edu 2.6.32-504.23.4.el6.x86_64 #1 SMP
Tue Jun 9 20:57:37 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
------------------
1. Smithy Function()
The tests found a bug in the function. The test checks for the amount of cards in the
players hand compared to what they should have. This function fails the test. The test
was expecting 7 cards, but got 5. This function is not discarding the proper amount of
cards.
The function interface was not the same, so I needed to change the tests call feature
of the function.
The bug was found on line 25 of dominion.c-->discardCard(handPos, currentPlayer, state, 1);
The number 1 for the discard function should be number 0.

Printout from Test:
TESTING THE ** Smithy Card ** Function

TEST 1 for player 1.
TEST: ** PASSED ** because hand had 7 amount of cards.

TEST 2 for player 2.
TEST: ** FAILED ** because hand had 5 cards instead of 7 cards.

Not every test passed

DONE TESTING ** Smithy Card ** FUNCTION

File 'dominion.c'
Lines executed:18.14% of 590
Branches executed:17.75% of 417
Taken at least once:14.15% of 417
Calls executed:9.90% of 101
dominion.c:creating 'dominion.c.gcov'


2. Adventurer Function()
The tests found a bug in the function. The test is designed to check of the players
hand count has increased after playing the adventurer card. This function fails every
test. The function will always return two less cards then what it should. i.e. expects
5 cards, receives.
The function interface was not the same, so I needed to change the tests call feature
of the function.
The bug was found on line 35 of dominion.c--> if (state->deckCount[currentPlayer] <= 1)
The number 1 should be number 0.


Printout from Test:
TESTING THE ** Adventurer Card ** Function

FIRST TEST: ** FAILED ** Expected Cards 7, got cards 5

SECOND TEST: ** FAILED ** Expected Cards 8, got cards 6

THIRD TEST: ** FAILED ** Expected Cards 9, got cards 7

Not every test passed

DONE TESTING ** Adventurer Card ** FUNCTION

File 'dominion.c'
Lines executed:37.29% of 590
Branches executed:40.05% of 417
Taken at least once:32.13% of 417
Calls executed:23.76% of 101







Teammate2Dominion  -- Guangting N
Platform: Linux flip2.engr.oregonstate.edu 2.6.32-504.23.4.el6.x86_64 #1 SMP
Tue Jun 9 20:57:37 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
------------------
1. Smithy Function()
The tests found a bug in the function. The test checks for the amount of cards in the
players hand compared to what they should have. This function fails the test. The test
was expecting 7 cards, but got 6. This function is not discarding the proper amount of
cards. It is always failing by one. There is also an unused variable: trashFlag
The function interface was not the same, so I needed to change the tests call feature
of the function.
The bug was found on line 678 of dominion.c-->  for (i = 1; i < 3; i++) i=1 should be
i=0.

Printout from Test:
TESTING THE ** Smithy Card ** Function

TEST 1 for player 1.
TEST: ** FAILED ** because hand had 6 cards instead of 7 cards.

TEST 2 for player 2.
TEST: ** FAILED ** because hand had 6 cards instead of 7 cards.

Not every test passed

DONE TESTING ** Smithy Card ** FUNCTION

File 'dominion.c'
Lines executed:18.24% of 581
Branches executed:17.83% of 415
Taken at least once:14.22% of 415
Calls executed:9.47% of 95
dominion.c:creating 'dominion.c.gcov'


2. Village Function()
The tests found a bug in the function.  The test is designed to check if the number of
actions are correct after running the function. The function fails every test, by always
adding 1 to the number of actions it should have.
The function interface was not the same, so I needed to change the tests call feature
of the function.
The bug appears to be on line 714 of dominion.c-->state->numActions = state->numActions++;
The number of actions is being incremented by one and not two.

Printout from Test:
TESTING THE ** Village Card ** Function

TEST 1 for player 1.
TEST: ** FAILED ** because Number of Actions are 7 instead of 8 cards.

TEST 2 for player 2.
TEST: ** FAILED ** because Number of Actions are 13 instead of 14 cards.

Not every test passed

DONE TESTING ** Village Card ** FUNCTION

File 'dominion.c'
Lines executed:21.86% of 581
Branches executed:20.72% of 415
Taken at least once:16.39% of 415
Calls executed:12.63% of 95
dominion.c:creating 'dominion.c.gcov'


3. CouncilRoom Function()
The tests found a bug in the function.  The test is designed to check if the original
hand count is equal to the new hand count. This particular function always fails when it
is players 2 turn.
The function interface was not the same, so I needed to change the tests call feature
of the function.
The bug appears to be a missing piece of logic, where it needs to check if the i counter
is the current player.

Printout from Test:
TESTING THE ** Council Room Card ** Function


TESTING when Player 1 has the  ** Council Room Card **

TEST 1: ** FAILED **  Player 1 has 9 cards and should have 12 cards.
TEST 1: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 1: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 1: ** PASSED **  Player 1 has 6 cards and should have 6 cards.

TESTING when Player 2 has the  ** Council Room Card **

TEST 2: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 2: ** FAILED ** Player 2  had 9 cards, should of had 10
TEST 2: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 2: ** PASSED **  Player 1 has 6 cards and should have 6 cards.

TESTING when Player 3 has the  ** Council Room Card **

TEST 3: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 3: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 3: ** FAILED ** Player 2  had 9 cards, should of had 10
TEST 3: ** PASSED **  Player 1 has 6 cards and should have 6 cards.

TESTING when Player 4 has the  ** Council Room Card **

TEST 4: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 4: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 4: ** PASSED **  Player 1 has 6 cards and should have 6 cards.
TEST 4: ** FAILED ** Player 2  had 9 cards, should of had 10

Not every test passed
DONE TESTING ** Council Room Card ** FUNCTION

File 'dominion.c'
Lines executed:24.27% of 581
Branches executed:22.17% of 415
Taken at least once:18.31% of 415
Calls executed:15.79% of 95
dominion.c:creating 'dominion.c.gcov'






































































































