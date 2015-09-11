#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Testing the isGameOver() function

int main () 
{
	int r, i, n, notPassing;
	int seed = 1000;
	int numPlayer = 2;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
	//Taken from class lecture
    printf ("\nTESTING THE ** isGameOver() ** Function \n\n");
    memset(&G, 23, sizeof(struct gameState));   // Used to clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // Used to initialize the game 
	
	printf("First Test: Game will end when province counter == 0. The count down begins at %d\n", G.supplyCount[province]);
	for(i=G.supplyCount[province]; i >= 0; i--)
	{
		G.supplyCount[province] = i;
		n = isGameOver(&G);
		if (n == 0)
		{
			printf("First Test: ** PASSED ** game DID NOT end, because province was at %d\n", G.supplyCount[province]);			
		}
		else if (i == 0 && n == 1)
		{
			printf("First Test: ** PASSED ** game DID end, because province was at %d\n", G.supplyCount[province]);
		}
		else if (i == 0 && n == 0)
		{
			printf("First Test: ** FAILED ** because game ended when %d province cards existed\n", G.supplyCount[province]);
			notPassing++;
		}
		else 
		{
			printf("First Test: ** FAILED ** because game ended when %d province cards existed\n", G.supplyCount[province]);
			notPassing++;
		}
	}
	
	// Restocking the province card here
	G.supplyCount[province] = 3;
	
	printf("\nSecond Test: Validating that if supplyCount[i] equals 0 for 3 times that the game ends\n");
		
    for(i = 0; i < 25; i++) 
	{
        G.supplyCount[i] = 0;
        if(i < 2) 
		{ 
			n = isGameOver(&G);
            if(n == 0) 
			{
                printf("Second Test: ** PASSED ** The game CONTINUED, because supplyCount == 0 %d time(s) \n", i+1);
            }
            else 
			{
                printf("Second Test: ** FAILED ** The game continued, even though the supplyCounter was %d\n", i+1);
                notPassing++;
            }
        }
        else 
		{ 
			n = isGameOver(&G);
            if(n == 1) 
			{
                printf("Second Test: ** PASSED ** The game ENDED, because the supplyCount == 0 %d times.\n", i+1);
            }
            else 
			{
                printf("Second Test: ** FAILED ** The game did not end, even though the supplyCounter was %d.\n", i+1);
                notPassing++;
            }
        }
    }
		
	if(notPassing > 0)
	{
		printf("Not every test passed\n");
	}
	else
	{
		printf("All test Passed\n");
	}
	
	printf("\nDONE TESTING ** isGameOver() ** FUNCTION \n\n");
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	