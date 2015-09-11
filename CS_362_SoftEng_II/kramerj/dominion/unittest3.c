#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Testing the getCost() function

int main () 
{
	int r, i, n, notPassing;
	int seed = 1000;
	int numPlayer = 2;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
	//Taken from class lecture
    printf ("\nTESTING THE ** getCost() ** Function \n\n");
    memset(&G, 23, sizeof(struct gameState));   // Used to clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // Used to initialize the game
	
    const char *nameOfCards[28] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	int costOfCards[28] = {0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	
	for (i=0; i<27; i++)
	{
		n = getCost(i);
		if(n == costOfCards[i])
		{
			printf("Test: ** PASSED ** Card %s == Cost %d\n", nameOfCards[i], costOfCards[i]);
		}
		else
		{
			printf("Test: ** FAILED ** Card %s != Cost %d\n", nameOfCards[i], costOfCards[i]);
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
	

	printf("\nDONE TESTING ** getCost() ** FUNCTION \n\n");
	return 0;
}