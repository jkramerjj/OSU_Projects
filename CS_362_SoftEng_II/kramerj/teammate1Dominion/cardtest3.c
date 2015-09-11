#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Testing the Village Card function

int main () 
{
	int i;
	int notPassing = 0;
	int seed = 1000;
	int numPlayer = 2;
	int p, r, handCount, actionCount, handPos;
	int k[10] = {adventurer, council_room, feast, gardens, mine
				, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int genericHand[MAX_HAND];

	printf ("\nTESTING THE ** Village Card ** Function \n\n");
	for (i = 0; i < MAX_HAND; i++)
	{
		genericHand[0] = gold; 
		genericHand[1] = curse;
		genericHand[2] = adventurer;
		genericHand[3] = smithy;
		genericHand[4] = village;
	}

	handPos = 4; 		// used to hold the location of village 
	handCount = 3;		// Used to set the number of cards 
	actionCount = 6; 	// used to set the amount of action

	for (p = 0; p < numPlayer; p++)
	{
		printf("TEST %d for player %d.\n", p+1, p+1);               
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = handCount;                 // Used to set the number of cards 
		G.numActions = actionCount * (p+1);			// used to set the amount of action
		
		memcpy(G.hand[p], genericHand, sizeof(int) * handCount); // Used to set cards to genericHand
		
		//printf("This b4 Numaction == %d\n", G.numActions);
		
		playVillage(&G,  handPos);
		
		//printf("This after Numaction == %d\n", G.numActions);
			
		
		if(G.numActions == actionCount * (p+1) + 2) 
		{
			printf("TEST: ** PASSED ** because Number of Actions are %d.\n\n", G.numActions );
		}
		else
		{
			//actionCount = actionCount * (p+1);
			printf("TEST: ** FAILED ** because Number of Actions are %d instead of %d cards.\n\n",G.numActions, actionCount * (p+1) + 2);
			notPassing++;	
		}
	}

	if(notPassing > 0)
	{
		printf("Not every test passed\n");
	}
	else
	{
		printf("All tests passed\n");
	}	

	
	printf("\nDONE TESTING ** Village Card ** FUNCTION \n\n");
	    
	return 0;

}