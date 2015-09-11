unittest1.c -- Shuffle Function
1. There does not appear to be a bug with this test. 
2. The test is designed to take decks and make them equal to each other. It then runs
each deck though the shuffle function and checks to see if they are the same. Each time 
the test is ran the decks are different. 

unittest2.c -- isGameOver Function
1. There does not appear to be a bug with this test. 
2. The test is designed to first check that the game will end when the "Province" counter
equals 0. The count begins at 8 and when it reaches 0 the games ends. It passes this test 
every time.  The second test starts the supply count at 3 and once it reaches 0 the game 
ends. It passed this test each time and even after hitting 3 it continues to pass the 
test up until it ends at 25 tries. 

unittest3.c -- getCost Function
1. I can reasonably say there are NO bugs in this code. 
2. The test is designed to check each cards value. The test it's self is simple. It takes
the known cost of each card and compares it to the program given cost. The test passed 
each test. All costs are correct.

unittest4.c -- supplyCount Function
1. I can reasonably say there are NO bugs in this code. 
2. The test is designed to check function returns the same value as direct struct access 
would. The first test directly compare the suppyCount function to the struct and the test 
passes. The second test changes the supply count of each card and then calls the 
supplyCount function to verify. All these tests passed. Finally the last test changes 
only 10 cards values and then checks those. All 10 cards pass.

cardtest1.c -- Smithy Card
1. There is a bug.  
2. First bug. I spelled Smithy wrong. The function is coded as: simthyFunction. 
3. Second bug. I coded in for Smithy to call one extra drawcard, much means the players 
hand would have one extra card. This bug happened every-time the test was ran. 

cardtest2.c -- Adventurer Card 
1. There is a bug. 
2. I updated the bug to be drawtreasure+2. In the test I have to code call the Adventurer 
function and then check to see if it adds two cards to the hand. Each time it fails to 
add two cards. It is only adding one card. 

cardtest3.c -- Village Card
1. There is a bug. 
2. I updated the bug to be state->numActions = state->numActions + 3; In the test code I 
compared the returned action numbers to the correct action numbers. Each time the action 
number returned was one higher the correct action number, which makes sense since 3-2=1, 
therefore the difference will always be one more than regulation. 

cardtest4.c -- Council_Room
1. There is a bug. 
2. This bug only effects player 1 when player 1 is NOT playing the council_room card. The 
bug is in the second for-loop and instead of i=0, i equals 1, which means player[0] gets 
skipped when adding cards. The test indicates that all other players get their cards, 
whether then play the Council_Room or not. It's only player1 that will not get extra 
cards if someone else player Council_Room.




 



