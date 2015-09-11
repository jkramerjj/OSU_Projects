// Random Testing of Smithy Card


#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>

#define NUM_OF_TESTS 50000

void testSmithyFunction()
{	
    srand(time(NULL)); 
	int i, j;
    int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int numOfCardsForHand;
	int cardPosition, beforeCounter, afterCounter;
	int numPlayer = 2;
	int success = 0;
	int errors = 0;
	int printIt = 0;	// have printIt == 1 to print	
	
	printf("*** TEST 1a: %d ITERATIONS OF THE SMITHY FUNCTION ****\n", NUM_OF_TESTS);
	for(i = 0; i < NUM_OF_TESTS; i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		numOfCardsForHand = (rand() % 100) + 1;
		G.whoseTurn = rand()%2;
		
		G.handCount[G.whoseTurn] = numOfCardsForHand;	// Used to set the number of cards in the hand. 
				
		// Used to place random cards in the hand. 
		for(j = 0; j < numOfCardsForHand; j++)
		{
			G.hand[G.whoseTurn][j] =  floor(rand() % 17 + 1);
		}		
		
		cardPosition = rand() % numOfCardsForHand;		// used to find a random card position umber
		G.hand[G.whoseTurn][cardPosition] = smithy;		// used to place smithy into a random location in player x's hand			
		beforeCounter = numOfCardsForHand;				// Used to record the number of cards b4 the function call
		
		playSmithy(&G, cardPosition);
		
		afterCounter = G.handCount[G.whoseTurn];		// Used to record the number of cards after the function call
				
		if(afterCounter != beforeCounter + 2)
		{
			if (printIt == 1)
			{
				printf("Test_%i Section 1 ** FAILED ** because the card totals are not equal. PROOF: %d == %d\n", i, afterCounter, beforeCounter);
			}
			errors++;
		}
		else
		{			
			if (printIt == 1)
			{
				printf("Test_%i Section 1 ** PASSED ** because the card totals are equal. PROOF: %d == %d\n", i, afterCounter, beforeCounter);
			}
			success++;
		}
	}
	printf("Total Successes: %d\n", success);
	printf("Total Errors: %d\n", errors);	
}


void testPlayCardFunction()
{		
    int i, j;
    int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	int numOfCardsForHand;
	int cardPosition, beforeCounter, afterCounter;
	int numPlayer = 2;
	int success = 0;
	int errors = 0;
	int printIt = 0;	// have printIt == 1 to print
	
	srand(time(NULL)); 
	
	printf("\n*** TEST 1b: %d ITERATIONS OF THE SMITHY FUNCTION VIA THE PLAYCARD FUNCTION ****\n", NUM_OF_TESTS);
	for(i = 0; i < NUM_OF_TESTS; i++)
	{
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		initializeGame(numPlayer, k, seed, &G);
		numOfCardsForHand = (rand() % 100) + 1;
		G.whoseTurn = rand()%2;
		
		G.handCount[G.whoseTurn] = numOfCardsForHand;	// Used to set the number of cards in the hand. 
				
		// Used to place random cards in the hand. 
		for(j = 0; j < numOfCardsForHand; j++)
		{
			G.hand[G.whoseTurn][j] =  floor(rand() % 17 + 1);
		}		
		
		cardPosition = rand() % numOfCardsForHand;		// used to find a random card position umber
		G.hand[G.whoseTurn][cardPosition] = smithy;		// used to place smithy into a random location in player x's hand			
		beforeCounter = numOfCardsForHand;				// Used to record the number of cards b4 the function call
		
		playCard(cardPosition, -1, -1, -1, &G);	
		
		afterCounter = G.handCount[G.whoseTurn];		// Used to record the number of cards after the function call
				
		if(afterCounter != beforeCounter + 2)
		{
			if (printIt == 1)
			{
				printf("Test_%i Section 2 ** FAILED ** because the card totals are not equal. PROOF: %d == %d\n", i, afterCounter, beforeCounter);
			}
			errors++;
		}
		else
		{			
			if (printIt == 1)
			{
				printf("Test_%i Section 2 ** PASSED ** because the card totals are equal. PROOF: %d == %d\n", i, afterCounter, beforeCounter);
			}
			success++;
		}
	}
	printf("Total Successes: %d\n", success);
	printf("Total Errors: %d\n\n\n", errors);
}


int main() 
{	
	printf("\n\nRandom Tester: SMITHY\n");	
	testSmithyFunction();
	testPlayCardFunction();	
	return 0;
}












































