#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


// Testing the supplyCount() function

int main () 
{
	int r, i, n, notPassing;
	int seed = 1000;
	int numPlayer = 2;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
	
	//Taken from class lecture
    printf ("\nTESTING THE ** supplyCount() ** Function \n\n");
    memset(&G, 23, sizeof(struct gameState));   // Used to clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // Used to initialize the game 
		
	//for(i=0; i<27; i++)
//	{
	//	n = supplyCount(i, &G);
	//	printf("N == %d\n", n);
	//}
	
	printf("First Test: Make sure supplyCount() function returns the correct initial values");
    for(i = 0; i < 27; i++) 
	{
		n = supplyCount(i, &G); 
    	if(n == G.supplyCount[i]) 
		{
    		printf("First Test: ** PASSED ** Card[%d] == %d \n", i, G.supplyCount[i]);
    	}
    	else
		{
    		printf("First Test: ** FAILED ** Card[%d] == %d \n", i, G.supplyCount[i]);
    		notPassing++;
    	}
    }
	
	printf("\nSecond Test: Change supply count on all cards to verify that it returns the correct number.\n");
    for(i = 0; i < 27; i++) 
	{
    	G.supplyCount[i] = i;
		n = supplyCount(i, &G);
    	if(n == G.supplyCount[i]) 
		{
    		printf("Second Test: ** PASSED ** Card[%d] == %d \n", i, n);
    	}
    	else 
		{
    		printf("Second Test: ** FAILED ** Card[%d] == %d \n", i, n);
    		notPassing++;
    	}
    }
	
    printf("\nThird Test: Change supply count on \" int k[10] = {adventurer, council_room,\nfeast, gardens, mine, remodel, smithy, village, baron, great_hall\" to\nverify that it returns the correct value.\n");
    for(i = 0; i < 10; i++) 
	{
    	G.supplyCount[k[i]] = i;
		n = supplyCount(k[i], &G);
    	if(n == G.supplyCount[k[i]]) 
		{
    		printf("Third Test: ** PASSED ** Card[%d] == %d \n", i, n);
    	}
    	else 
		{
    		printf("Third Test: ** FAILED ** Card[%d] == %d \n", i, n);
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
	
	printf("\nDONE TESTING ** supplyCount() ** FUNCTION \n\n");
	
	return 0;
	
}
































