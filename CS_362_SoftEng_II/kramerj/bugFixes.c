Niguang Dominion -- Bugs Found
------------------
Smithy Function()
In the dominion.c file on line 650 I changed the code from for (i = 0; i <= 3; i++) to
for (i = 0; i < 3; i++). This fixed the bug of each time G.handcount was greater
than the expected value by 1, not it is equal. 

Adventurer Function()
In the dominion.c file on line 675 I changed drawntreasure = drawntreasure + 2 to
drawntreasure = drawntreasure++.  That fixed the bug of of discarding one more card than
it should. 

Village Function()
In the domionion.c file on line 723 I changed state->numActions = state->numActions + 3 
to state->numActions = state->numActions + 2.  This fixed the bug of one more action
being available to the player. 



Eric Dominion -- Bugs Found
------------------
Smithy Function()
Found issue with line 650.   ** Already Fixed
Found issue with spelling of smithy function on 647. Changed from simthyFunction to
smithyFunction
  
Adventurer Function()
Found issue with line 675.   ** Already Fixed

Village Function()
Found issue with line 723.   ** Already Fixed




Unfound Bugs
------------------
Council_Room Function()
There was a bug that would only effects player 1 when player 1 is NOT playing the 
council_room card. It's only player1 that will not get extra cards if someone else player 
Council_Room.  I change line 703 of dominion.c from for (i = 1; i < state->numPlayers; i++)
to for (i = 0; i < state->numPlayers; i++)



































































