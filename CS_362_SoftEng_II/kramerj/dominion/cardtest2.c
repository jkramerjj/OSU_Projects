#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Testing the Adventurer Card function

int main () 
{
	int i, notPassing;
    int seed = 500;
    int numPlayer = 2;
    struct gameState G;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};
   

    initializeGame(numPlayer, k, seed, &G); // initialize a new game
	notPassing = 0;
	printf ("\nTESTING THE ** Adventurer Card ** Function \n\n");    
	
	// Used to fill with curse cards	
    for(i = 0; i < 5; i++) 
	{
        G.hand[1][i] = curse;
        G.handCount[1]++;
    }
	
    //printf("FIRST TEST: Expected Cards %d, got cards %d\n", 5, G.handCount[1]);
    adventurerFunction(1, &G);
	if(7 == G.handCount[1])
	{
		printf("FIRST TEST: ** PASSED ** Expected Cards %d, got cards %d\n\n",7, G.handCount[1]);
	}
	else
	{
		printf("FIRST TEST: ** FAILED ** Expected Cards %d, got cards %d\n\n",7, G.handCount[1]);
		notPassing++;
	}
	
	// Reset hand counter
	G.handCount[1] = 0;	
	
	// Used to fill with curse cards
	for(i = 0; i < 6; i++) 
	{
        G.hand[1][i] = curse;
        G.handCount[1]++;
    }
	
	adventurerFunction(1, &G);
	if(8 == G.handCount[1])
	{
		printf("SECOND TEST: ** PASSED ** Expected Cards %d, got cards %d\n\n",8, G.handCount[1]);
	}
	else
	{
		printf("SECOND TEST: ** FAILED ** Expected Cards %d, got cards %d\n\n",8, G.handCount[1]);
		notPassing++;
	}

	// Reset hand counter
	G.handCount[1] = 0;
	
	// Used to fill with curse cards
	for(i = 0; i < 7; i++) 
	{
        G.hand[1][i] = curse;
        G.handCount[1]++;
    }	
	
	adventurerFunction(1, &G);
	if(9 == G.handCount[1])
	{
		printf("THIRD TEST: ** PASSED ** Expected Cards %d, got cards %d\n\n",9, G.handCount[1]);
	}
	else
	{
		printf("THIRD TEST: ** FAILED ** Expected Cards %d, got cards %d\n\n",9, G.handCount[1]);
		notPassing++;
	}
	
	
	if(notPassing > 0)
	{
		printf("Not every test passed\n");
	}
	else
	{
		printf("All tests passed\n");
	}	

	
	printf("\nDONE TESTING ** Adventurer Card ** FUNCTION \n\n");
	    
    return 0;


}









































