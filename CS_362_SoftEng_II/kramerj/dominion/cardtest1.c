#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Testing the Smithy Card function

int main () 
{
	int i;
	int notPassing = 0;
	int seed = 1000;
	int numPlayer = 2;
	int p, r, handCount;
	int k[10] = {adventurer, council_room, feast, gardens, mine
				, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int genericHand[MAX_HAND];

	printf ("\nTESTING THE ** Smithy Card ** Function \n\n");
	for (i = 0; i < MAX_HAND; i++)
	{
		genericHand[0] = gold; 
		genericHand[1] = curse;
		genericHand[2] = adventurer;
		genericHand[3] = village;
		genericHand[4] = smithy;
	}

	int handPos = 4; // used to hold the location of smithy 
	handCount = 5;

	for (p = 0; p < numPlayer; p++)
	{
		printf("TEST %d for player %d.\n", p+1, p+1);               
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
		G.handCount[p] = handCount;                 // Used to set the number of cards 

		memcpy(G.hand[p], genericHand, sizeof(int) * handCount); // Used to set cards to genericHand
		simthyFunction(p, &G,  handPos);

		if(G.handCount[p] == handCount + 2) 
		{
			printf("TEST: ** PASSED ** because hand had %d amount of cards.\n\n", handCount + 2 );
		}
		else
		{
			printf("TEST: ** FAILED ** because hand had %d cards instead of %d cards.\n\n",G.handCount[p], handCount + 2  );
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

	printf("\nDONE TESTING ** Smithy Card ** FUNCTION \n\n");
	return 0;

}

























