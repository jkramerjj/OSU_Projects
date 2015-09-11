// Random Testing of Adventurer Card

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NUM_OF_TESTS 50000

int n, r, i, j;
int previousTreasureTotal;
int afterTreasureTotal;
int passed = 0;
int seed = 1000;
int numPlayer = 2;	
int k[10] = {adventurer, council_room, feast, gardens, mine
		   , remodel, smithy, village, baron, great_hall};

int printIt = 0; // have printIt == 1 to print

// Testing the adventurer() function


void testAdventurerFunction()
{
	printf("*** TEST 1a: %d ITERATIONS OF THE ADVENTURER FUNCTION WITH GUARANTEED 2+ TREASURE CARDS IN DECK  ****\n", NUM_OF_TESTS);	
	struct gameState G;
	int success = 0;
	int errors = 0;
	
	for(i=0; i<NUM_OF_TESTS; i++)
	{
		previousTreasureTotal = 0;
		afterTreasureTotal = 0;
		
		memset(&G, 23, sizeof(struct gameState));   // Used to clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // Used to initialize the game

		// used to pick a random player
		G.whoseTurn = floor(rand() % MAX_PLAYERS + 1);
		
		// Used to put random amount of cards in the deck. 
		G.deckCount[whoseTurn(&G)] = floor(rand() % MAX_DECK + 1);
		
		// Used to put random num of cards in hand
        G.handCount[whoseTurn(&G)] = floor(rand() % MAX_HAND + 1); 
		
		// Used to set the discarded cards to the amount that's left. 
		G.discardCount[whoseTurn(&G)] = (MAX_DECK - (G.deckCount[whoseTurn(&G)] = G.handCount[whoseTurn(&G)]));		
		
		// Used to place real cards into the hands. All cards a randomly chosen.
        for(j = 0; j < G.deckCount[whoseTurn(&G)]; j++) 
		{
            G.deck[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) 
		{
            G.hand[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < G.discardCount[whoseTurn(&G)]; j++) 
		{
            G.discard[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }	 
	 
		// Used to place the adventurer card in a random spot
        int cardPosition = floor(rand() % G.handCount[whoseTurn(&G)] + 1);
        G.hand[whoseTurn(&G)][cardPosition] = adventurer;
		
        int allCards = G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)];

        // Used to total the number of treasure cards 
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) 
		{
            if(G.hand[whoseTurn(&G)][j] == copper || G.hand[whoseTurn(&G)][j] == silver || G.hand[whoseTurn(&G)][j] == gold) 
			{
                previousTreasureTotal++;
            }
        }		
		
		// If the deck has less then 2 coins cards, it will skip the this round of testing
		// basically everything is randomly set up, but we need to make sure some coins are atleast
		// randomly entered into the deck.
		int coinChecker =0;
        for(j = 0; j < G.deckCount[whoseTurn(&G)]; j++) 
		{
            if(G.deck[whoseTurn(&G)][j] == copper || G.deck[whoseTurn(&G)][j] == silver || G.deck[whoseTurn(&G)][j] == gold) 
			{
                coinChecker++;
            }			
        }
		// If the deck has more then 2 coins, it is ok to proceed with the test.
		// Otherwise start over. 
		if(coinChecker > 2)
		{
			// This is will play the adventurer card
			adventurerFunction(whoseTurn(&G), &G); 

			// Used to total the number of treasure cards 
			for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) 
			{
				if(G.hand[whoseTurn(&G)][j] == copper || G.hand[whoseTurn(&G)][j] == silver || G.hand[whoseTurn(&G)][j] == gold) 
				{
					afterTreasureTotal++;
				}
			}
			
			// From this point the program will verify the results. 		   
			// Used to verify the total number of cards
			if(G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)] != allCards - 2) 
			{
				if (printIt == 1)
					printf("Test_%i Section 1 ** FAILED ** because the before and after card totals are not equal. PROOF: %d != %d\n", i, G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)], allCards - 2);
				errors++;
			}
			else
			{
				if (printIt == 1)
					printf("Test_%i Section 1 ** PASSED ** because the before and after card totals are equal. PROOF: %d == %d\n", i, G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)], allCards - 2);
				success++;
			}

			//Used to verify that there should be 2 more treasure cards in the deck. 
			if(afterTreasureTotal != previousTreasureTotal + 2) 
			{
				if (printIt == 1)
					printf("Test_%i Section 2 ** FAILED ** because the total number of treasure cards are not equal. PROOF: %d != %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				errors++;
			}
			else
			{
				if (printIt == 1)
					printf("Test_%i Section 2 ** PASSED ** because the total number of treasure cards are equal. PROOF: %d == %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				success++;
			}
		}
	}
	printf("Total successes: %d\n", success);
	printf("Total Errors: %d\n", errors);
}


void testAdventurerFunction2()
{
	printf("\n**** TEST 1b: %d ITERATIONS OF THE ADVENTURER FUNCTION NO WITH GUARANTEE OF TREASURE CARDS IN DECK ****\n", NUM_OF_TESTS);	
	struct gameState G;
	int success = 0;
	int errors = 0;
	
	for(i=0; i<NUM_OF_TESTS; i++)
	{
		previousTreasureTotal = 0;
		afterTreasureTotal = 0;
		
		memset(&G, 23, sizeof(struct gameState));   // Used to clear the game state
		r = initializeGame(numPlayer, k, seed, &G); // Used to initialize the game

		// used to pick a random player
		G.whoseTurn = floor(rand() % MAX_PLAYERS + 1);
		
		// Used to put random amount of cards in the deck. 
		G.deckCount[whoseTurn(&G)] = floor(rand() % MAX_DECK + 1);
		
		// Used to put random num of cards in hand
        G.handCount[whoseTurn(&G)] = floor(rand() % MAX_HAND + 1); 
		
		// Used to set the discarded cards to the amount that's left. 
		G.discardCount[whoseTurn(&G)] = (MAX_DECK - (G.deckCount[whoseTurn(&G)] = G.handCount[whoseTurn(&G)]));		
		
		// Used to place real cards into the hands. All cards a randomly chosen.
        for(j = 0; j < G.deckCount[whoseTurn(&G)]; j++) 
		{
            G.deck[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) 
		{
            G.hand[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < G.discardCount[whoseTurn(&G)]; j++) 
		{
            G.discard[whoseTurn(&G)][j] = floor(rand() % 17 + 1);
        }	 
	 
		// Used to place the adventurer card in a random spot
        int cardPosition = floor(rand() % G.handCount[whoseTurn(&G)] + 1);
        G.hand[whoseTurn(&G)][cardPosition] = adventurer;
		
        int allCards = G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)];

        // Used to total the number of treasure cards 
        for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) 
		{
            if(G.hand[whoseTurn(&G)][j] == copper || G.hand[whoseTurn(&G)][j] == silver || G.hand[whoseTurn(&G)][j] == gold) 
			{
                previousTreasureTotal++;
            }
        }		
		
		// If the deck has less then 2 coins cards, it will skip the this round of testing
		// basically everything is randomly set up, but we need to make sure some coins are atleast
		// randomly entered into the deck.
		int coinChecker =0;
        for(j = 0; j < G.deckCount[whoseTurn(&G)]; j++) 
		{
            if(G.deck[whoseTurn(&G)][j] == copper || G.deck[whoseTurn(&G)][j] == silver || G.deck[whoseTurn(&G)][j] == gold) 
			{
                coinChecker++;
            }			
        }
		// If the deck has more then 2 coins, it is ok to proceed with the test.
		// Otherwise start over. 
		if(coinChecker > 2)
		{
			// This is will play the adventurer card
			adventurerFunction(whoseTurn(&G), &G); 

			// Used to total the number of treasure cards 
			for(j = 0; j < G.handCount[whoseTurn(&G)]; j++) 
			{
				if(G.hand[whoseTurn(&G)][j] == copper || G.hand[whoseTurn(&G)][j] == silver || G.hand[whoseTurn(&G)][j] == gold) 
				{
					afterTreasureTotal++;
				}
			}
			
			// From this point the program will verify the results. 		   
			// Used to verify the total number of cards
			if(G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)] != allCards - 2) 
			{
				if (printIt == 1)
					printf("Test_%i Section 1 ** FAILED ** because the before and after card totals are not equal. PROOF: %d != %d\n", i, G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)], allCards - 2);
				errors++;
			}
			else
			{
				if (printIt == 1)
					printf("Test_%i Section 1 ** PASSED ** because the before and after card totals are equal. PROOF: %d == %d\n", i, G.deckCount[whoseTurn(&G)] + G.discardCount[whoseTurn(&G)], allCards - 2);
				success++;
			}

			//Used to verify that there should be 2 more treasure cards in the deck. 
			if(afterTreasureTotal != previousTreasureTotal + 2) 
			{
				if (printIt == 1)
					printf("Test_%i Section 2 ** FAILED ** because the total number of treasure cards are not equal. PROOF: %d != %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				errors++;
			}
			else
			{
				if (printIt == 1)
					printf("Test_%i Section 2 ** PASSED ** because the total number of treasure cards are equal. PROOF: %d == %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				success++;
			}
		}
	}
	printf("Total successes: %d\n", success);
	printf("Total Errors: %d\n", errors);
}


void testPlayCardFunction()
{			
	int success = 0;
	int errors = 0;	
	struct gameState H;
	
	printf("\n*** TEST 2a: %d ITERATIONS OF THROUGHT THE PLAYCARD FUNCTION WITH GUARANTEED 2+ TREASURE CARDS IN DECK ****\n", NUM_OF_TESTS);
	
	for(i=0; i<NUM_OF_TESTS; i++)
	{
		memset(&H, 23, sizeof(struct gameState));   // Used to clear the game state
		r = initializeGame(numPlayer, k, seed, &H); // Used to initialize the game

		// used to pick a random player
		H.whoseTurn = floor(rand() % MAX_PLAYERS + 1);
		
		// Used to put random amount of cards in the deck. 
		H.deckCount[whoseTurn(&H)] = floor(rand() % MAX_DECK + 1);
		
		// Used to put random num of cards in hand
        H.handCount[whoseTurn(&H)] = floor(rand() % MAX_HAND + 1); 
		
		// Used to set the discarded cards to the amount that's left. 
		H.discardCount[whoseTurn(&H)] = (MAX_DECK - (H.deckCount[whoseTurn(&H)] = H.handCount[whoseTurn(&H)]));
	
		
		//Now that you have # of cards in each, put actual cards in them
        for(j = 0; j < H.deckCount[whoseTurn(&H)]; j++) 
		{
            H.deck[whoseTurn(&H)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < H.handCount[whoseTurn(&H)]; j++) 
		{
            H.hand[whoseTurn(&H)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < H.discardCount[whoseTurn(&H)]; j++) 
		{
            H.discard[whoseTurn(&H)][j] = floor(rand() % 17 + 1);
        }
	 
		// Used to place the adventurer card in a random spot
        int cardPosition = floor(rand() % H.handCount[whoseTurn(&H)] + 1);
        H.hand[whoseTurn(&H)][cardPosition] = adventurer;
		
        int allCards = H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)];

        // Used to total the number of treasure cards 
        for(j = 0; j < H.handCount[whoseTurn(&H)]; j++) 
		{
            if(H.hand[whoseTurn(&H)][j] == copper || H.hand[whoseTurn(&H)][j] == silver || H.hand[whoseTurn(&H)][j] == gold) 
			{
                previousTreasureTotal++;
            }
        }
		
		// If the deck has less then 2 coins cards, it will skip the this round of testing
		// basically everything is randomly set up, but we need to make sure some coins are atleast
		// randomly entered into the deck.
		int coinChecker =0;
        for(j = 0; j < H.deckCount[whoseTurn(&H)]; j++) 
		{
            if(H.deck[whoseTurn(&H)][j] == copper || H.deck[whoseTurn(&H)][j] == silver || H.deck[whoseTurn(&H)][j] == gold) 
			{
                coinChecker++;
            }			
        }
		// If the deck has more then 2 coins, it is ok to proceed with the test.
		// Otherwise start over. 
		if(coinChecker > 2)
		{
			// Used to play the adventurer card through another method. 
			playCard(cardPosition, -1, -1, -1, &H);
			
			 // Used to total the number of treasure cards 
			for(j = 0; j < H.handCount[whoseTurn(&H)]; j++) 
			{
				if(H.hand[whoseTurn(&H)][j] == copper || H.hand[whoseTurn(&H)][j] == silver || H.hand[whoseTurn(&H)][j] == gold) 
				{
					afterTreasureTotal++;
				}
			}
					
			// From this point the program will verify the results. 		   
			// Used to verify the total number of cards
			if(H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)] != allCards - 2) 
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 1 ** FAILED ** because the before and after card totals are not equal. PROOF: %d != %d\n", i, H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)], allCards - 2);
				}
				errors++;
			}
			else
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 1 ** PASSED ** because the before and after card totals are equal. PROOF: %d == %d\n", i, H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)], allCards - 2);
				}
				success++;
			}

			//Used to verify that there should be 2 more treasure cards in the deck. 
			if(afterTreasureTotal != previousTreasureTotal + 2) 
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 2 ** FAILED ** because the total number of treasure cards are not equal. PROOF: %d != %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				}
				errors++;
			}
			else
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 2 ** PASSED ** because the total number of treasure cards are equal. PROOF: %d == %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				}
				success++;
			}
		}
	}
	
	printf("Total successes: %d\n", success);
	printf("Total Errors: %d\n", errors);
}
	

void testPlayCardFunction2()
{			
	int success = 0;
	int errors = 0;	
	struct gameState H;
	
	printf("\n**** TEST 2b: %d ITERATIONS OF THE PLAYCARD FUNCTION WITH NO GUARANTEE OF TREASURE CARDS IN DECK  ****\n", NUM_OF_TESTS);
	
	for(i=0; i<NUM_OF_TESTS; i++)
	{
		memset(&H, 23, sizeof(struct gameState));   // Used to clear the game state
		r = initializeGame(numPlayer, k, seed, &H); // Used to initialize the game

		// used to pick a random player
		H.whoseTurn = floor(rand() % MAX_PLAYERS + 1);
		
		// Used to put random amount of cards in the deck. 
		H.deckCount[whoseTurn(&H)] = floor(rand() % MAX_DECK + 1);
		
		// Used to put random num of cards in hand
        H.handCount[whoseTurn(&H)] = floor(rand() % MAX_HAND + 1); 
		
		// Used to set the discarded cards to the amount that's left. 
		H.discardCount[whoseTurn(&H)] = (MAX_DECK - (H.deckCount[whoseTurn(&H)] = H.handCount[whoseTurn(&H)]));
	
		
		//Now that you have # of cards in each, put actual cards in them
        for(j = 0; j < H.deckCount[whoseTurn(&H)]; j++) 
		{
            H.deck[whoseTurn(&H)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < H.handCount[whoseTurn(&H)]; j++) 
		{
            H.hand[whoseTurn(&H)][j] = floor(rand() % 17 + 1);
        }
        for(j = 0; j < H.discardCount[whoseTurn(&H)]; j++) 
		{
            H.discard[whoseTurn(&H)][j] = floor(rand() % 17 + 1);
        }
	 
		// Used to place the adventurer card in a random spot
        int cardPosition = floor(rand() % H.handCount[whoseTurn(&H)] + 1);
        H.hand[whoseTurn(&H)][cardPosition] = adventurer;
		
        int allCards = H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)];

        // Used to total the number of treasure cards 
        for(j = 0; j < H.handCount[whoseTurn(&H)]; j++) 
		{
            if(H.hand[whoseTurn(&H)][j] == copper || H.hand[whoseTurn(&H)][j] == silver || H.hand[whoseTurn(&H)][j] == gold) 
			{
                previousTreasureTotal++;
            }
        }
		
		// If the deck has less then 2 coins cards, it will skip the this round of testing
		// basically everything is randomly set up, but we need to make sure some coins are atleast
		// randomly entered into the deck.
		int coinChecker =0;
        for(j = 0; j < H.deckCount[whoseTurn(&H)]; j++) 
		{
            if(H.deck[whoseTurn(&H)][j] == copper || H.deck[whoseTurn(&H)][j] == silver || H.deck[whoseTurn(&H)][j] == gold) 
			{
                coinChecker++;
            }			
        }
		// If the deck has more then 2 coins, it is ok to proceed with the test.
		// Otherwise start over. 
		if(coinChecker > -1)
		{
			// Used to play the adventurer card through another method. 
			playCard(cardPosition, -1, -1, -1, &H);
			
			 // Used to total the number of treasure cards 
			for(j = 0; j < H.handCount[whoseTurn(&H)]; j++) 
			{
				if(H.hand[whoseTurn(&H)][j] == copper || H.hand[whoseTurn(&H)][j] == silver || H.hand[whoseTurn(&H)][j] == gold) 
				{
					afterTreasureTotal++;
				}
			}
					
			// From this point the program will verify the results. 		   
			// Used to verify the total number of cards
			if(H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)] != allCards - 2) 
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 1 ** FAILED ** because the before and after card totals are not equal. PROOF: %d != %d\n", i, H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)], allCards - 2);
				}
				errors++;
			}
			else
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 1 ** PASSED ** because the before and after card totals are equal. PROOF: %d == %d\n", i, H.deckCount[whoseTurn(&H)] + H.discardCount[whoseTurn(&H)], allCards - 2);
				}
				success++;
			}

			//Used to verify that there should be 2 more treasure cards in the deck. 
			if(afterTreasureTotal != previousTreasureTotal + 2) 
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 2 ** FAILED ** because the total number of treasure cards are not equal. PROOF: %d != %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				}
				errors++;
			}
			else
			{
				if (printIt == 1)
				{
					printf("Test_%i Section 2 ** PASSED ** because the total number of treasure cards are equal. PROOF: %d == %d\n", i, afterTreasureTotal, previousTreasureTotal + 2);
				}
				success++;
			}
		}
	}
	
	printf("Total successes: %d\n", success);
	printf("Total Errors: %d\n\n\n", errors);
}


int main () 
{
	srand(time(NULL));

    printf ("\nTESTING THE ** adventurer() ** Function \n\n");

	testAdventurerFunction();	// This test uses adventurerFunction	
	testPlayCardFunction();		// This test uses playCard 
	testAdventurerFunction2();	// This test uses adventurerFunction2
	testPlayCardFunction2();	// This test uses playCard2

	return 0;
}








































