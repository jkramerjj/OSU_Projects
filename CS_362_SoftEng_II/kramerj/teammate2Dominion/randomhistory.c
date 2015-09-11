Code coverage of file: 25.82%, branch coverage: 27.23%. Compare to the last time’s unit, both the coverage are lower, but we only test two functions this time. Let’s look into each funciton.
File 'dominion.c'
Lines executed:25.82% of 581
Branches executed:27.23% of 415
Taken at least once:18.55% of 415
Calls executed:14.74% of 95
dominion.c:creating 'dominion.c.gcov'


For the smithyCard function, each statement and each branch are tested. In the last time’s unit test, the statement and branch coverage is also 100%, however, in this random test, each statement has tested more times.

Function 'smithyCard'
Lines executed:100.00% of 5
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

   -:  675://refactor: Implement smithy card method here
     3000:  676:void smithyCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag){
        -:  677:   int i;
     9000:  678:   for (i = 1; i < 3; i++)
        -:  679:   {
     6000:  680:      drawCard(currentPlayer, state);
        -:  681:   }
        -:  682:                        
        -:  683:   //discard card from hand
     3000:  684:   discardCard(handPos, currentPlayer, state, 0);
     3000:  685:}

For the adventurerCard function, each statement and each branch are tested. In the last time’s unit test, the statement and branch coverage is also 100%, however, in this random test, each statement has tested more times.


Function 'adventurerCard'
Lines executed:100.00% of 17
Branches executed:100.00% of 12
Taken at least once:83.33% of 12
Calls executed:100.00% of 2

        -:  651://Refacotr: Implement adventurer card method here.
     3000:  652:void adventurerCard(struct gameState *state, int currentPlayer, int cardDrawn, int temphand[MAX_HAND]){
     3000:  653:     int drawntreasure=0;
     3000:  654:     int z=0;// this is the counter for the temp hand
    15837:  655:     while(drawntreasure<2){
     9837:  656:        if (state->handCount[currentPlayer] <1){//if the hand is empty we need to shuffle discard and add to deck
     1696:  657:          shuffle(currentPlayer, state);
        -:  658:        }
     9837:  659:        drawCard(currentPlayer, state);
     9837:  660:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    15837:  661:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
     6000:  662:          drawntreasure++;
        -:  663:        else{
     3837:  664:          temphand[z]=cardDrawn;
     3837:  665:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
     3837:  666:          z++;
        -:  667:        }
        -:  668:      }
     9837:  669:      while(z-1>=0){
     3837:  670:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
     3837:  671:        z=z-1;
        -:  672:      }
     3000:  673:}


