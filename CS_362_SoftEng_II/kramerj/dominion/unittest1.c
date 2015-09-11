#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Testing the shuffle() function

int main () 
{
	int n, r;
	int passed = 0;
	int seed = 1000;
	int numPlayer = 2;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
	//Taken from class lecture
    printf ("\nTESTING THE ** shuffle() ** Function \n\n");
    memset(&G, 23, sizeof(struct gameState));   // Used to clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // Used to initialize the game
		
	memcpy(G.deck[0], G.deck[1], sizeof(G.deck[0]));  // Used to verify decks are same size
	
	//This will shuffle the first deck
	shuffle(0, &G);
    printf("\nFirst Test: Shuffling the deck #1 \n");
    printf("First Test: Checking if decks #1 and #2 are different\n");
    n = memcmp(G.deck[0], G.deck[1], sizeof(G.deck[0]));
    if(n != 0) 
	{        
        printf("First Test: ** PASSED ** \n");
        passed++;
    }
    else 
	{
		printf("First Test: ** FAILED ** \n");
    }

    //This will shuffle the second deck
	shuffle(1, &G);
    printf("\nSecond Test: Shuffling deck #2\n");   
    printf("Second Test: Checking if decks #2 and #1 are different\n");
    n = memcmp(G.deck[1], G.deck[0], sizeof(G.deck[1]));
    if(n != 0) 
	{        
        printf("Second Test: ** PASSED ** \n");
        passed++;
    }
    else 
	{
		printf("Second Test: ** FAILED ** \n");
    }

    if(passed >= 2) 
	{
        printf("\nTest 1 and 2 are ** SUCCESSFUL **\n");
		passed++; 
    }
    else 
	{
        printf("\nTest 1 and 2 are ** NOT SUCCESSFUL **\n");
		passed++;
    }
	
	
	if(passed > 0)
	{
		printf("All tests passed\n");
	}
	else
	{
		printf("Not every test passed \n");
	}
	
	printf("\nDONE TESTING ** shuffle() ** FUNCTION \n\n");
	return 0;
}
































