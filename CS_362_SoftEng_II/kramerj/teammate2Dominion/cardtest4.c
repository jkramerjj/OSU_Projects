#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Testing the Council Room Card function

int main () 
{
	int i;
	int notPassing = 0;
	int seed = 1000;
	int numPlayer = 4;
	int  r, handCount, handPos;
	int k[10] = {adventurer, council_room, feast, gardens, mine
				, remodel, smithy, village, baron, great_hall};
	struct gameState G;
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	
	handPos = 4; 		// used to hold the location of council_room 
	handCount = 3;		// Used to set the number of cards 
	
	 G.deckCount[1] = 100;
	 G.deckCount[2] = 100;
	 G.deckCount[3] = 100;
	 
	
	G.handCount[1] = 5;
	G.handCount[2] = 5;
	G.handCount[3] = 5;
	
	int player1 = 1;
	int player2 = 2;
	int player3 = 3;
	int player4 = 4;
	int council_room_hand_location = 4;
	int player1OrgHandCount = 0;
	int player2OrgHandCount = 0;
	int player3OrgHandCount = 0;
	int player4OrgHandCount = 0;
	
	//card counter	
	
	printf ("\nTESTING THE ** Council Room Card ** Function \n\n");
	
	
	for(i=0; i < numPlayer; i++)
	{
	
	printf ("\nTESTING when Player %d has the  ** Council Room Card **  \n\n", i+1);
	player1OrgHandCount = G.handCount[player1-1];
	player2OrgHandCount = G.handCount[player2-1];
	player3OrgHandCount = G.handCount[player3-1];
	player4OrgHandCount = G.handCount[player4-1];

	councilRoomCard(council_room_hand_location, i, &G);	
	if((i == player1-1 && player1OrgHandCount == G.handCount[player1-1]-3 ) || (i == player1-1 && player1OrgHandCount == G.handCount[player1-1]-1 ) || (player1OrgHandCount == G.handCount[player1-1]-3) || (player1OrgHandCount == G.handCount[player1-1]-1))
	{
		printf("TEST %d: ** PASSED **  Player %d has %d cards and should have %d cards.\n",i+1, player1 ,G.handCount[0], G.handCount[0] );

	}
	else
	{
		if(i == 0)
		{
			printf("TEST %d: ** FAILED **  Player %d has %d cards and should have %d cards.\n",i+1, player1 ,G.handCount[0], G.handCount[0] + 3);
			notPassing++;
		}
		else 
		{
			printf("TEST %d: ** FAILED **  Player %d has %d cards and should have %d cards.\n",i+1, player1 ,G.handCount[0], G.handCount[0] + 1);
			notPassing++;
		}

	}
	//printf("THis is the hand of Player %d they have this %d cards.\n",player1 ,G.handCount[0] );

	if((i == player2-1 && player2OrgHandCount == G.handCount[player2-1]-3 ) || (i == player2-1 && player2OrgHandCount == G.handCount[player2-1]-1 ) || (player2OrgHandCount == G.handCount[player2-1]-3) || (player2OrgHandCount == G.handCount[player2-1]-1))
	{
		printf("TEST %d: ** PASSED **  Player %d has %d cards and should have %d cards.\n",i+1, player1 ,G.handCount[1], G.handCount[1] );

	}
	else
	{
		if(i == 0)
		{
			printf("TEST %d: ** FAILED ** Player %d  had %d cards, should of had %d\n",i+1, player2 ,G.handCount[1], G.handCount[1] + 3);
			notPassing++;
		}
		else 
		{
			printf("TEST %d: ** FAILED ** Player %d  had %d cards, should of had %d\n",i+1, player2 ,G.handCount[1], G.handCount[1] + 1);
			notPassing++;
		}

	}
	
	
	//printf("THis is the hand of Player %d they have this %d cards.\n",player2 ,G.handCount[1] );
	
	if((i == player3-1 && player3OrgHandCount == G.handCount[player3-1]-3 ) || (i == player3-1 && player3OrgHandCount == G.handCount[player3-1]-1 ) || (player3OrgHandCount == G.handCount[player3-1]-3) || (player3OrgHandCount == G.handCount[player3-1]-1))
	{
		printf("TEST %d: ** PASSED **  Player %d has %d cards and should have %d cards.\n",i+1, player1 ,G.handCount[2], G.handCount[2] );

	}
	else
	{
		if(i == 0)
		{
			printf("TEST %d: ** FAILED ** Player %d  had %d cards, should of had %d\n",i+1, player2 ,G.handCount[2], G.handCount[2] + 3);
			notPassing++;
		}
		else 
		{
			printf("TEST %d: ** FAILED ** Player %d  had %d cards, should of had %d\n",i+1, player2 ,G.handCount[2], G.handCount[2] + 1);
			notPassing++;
		}

	}
	
	//printf("THis is the hand of Player %d they have this %d cards.\n",player3 ,G.handCount[2] );
	
	if((i == player4-1 && player4OrgHandCount == G.handCount[player4-1]-3 ) || (i == player4-1 && player4OrgHandCount == G.handCount[player4-1]-1 ) || (player4OrgHandCount == G.handCount[player4-1]-3) || (player4OrgHandCount == G.handCount[player4-1]-1))
	{
		printf("TEST %d: ** PASSED **  Player %d has %d cards and should have %d cards.\n",i+1, player1 ,G.handCount[3], G.handCount[3] );

	}
	else
	{
		if(i == 0)
		{
			printf("TEST %d: ** FAILED ** Player %d  had %d cards, should of had %d\n",i+1, player2 ,G.handCount[3], G.handCount[3] + 3);
			notPassing++;
		}
		else 
		{
			printf("TEST %d: ** FAILED ** Player %d  had %d cards, should of had %d\n",i+1, player2 ,G.handCount[3], G.handCount[3] + 1);
			notPassing++;
		}

	}
	
	
	//printf("THis is the hand of Player %d they have this %d cards.\n",player4 ,G.handCount[3] );

	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	handPos = 4; 		// used to hold the location of council_room 
	handCount = 3;		// Used to set the number of cards 

	G.deckCount[1] = 100;
	G.deckCount[2] = 100;
	G.deckCount[3] = 100;
	
	G.handCount[1] = 5;
	G.handCount[2] = 5;
	G.handCount[3] = 5;
	
	player1 = 1;
	player2 = 2;
	player3 = 3;
	player4 = 4;
	
	council_room_hand_location = 4;
	}
	
	if(notPassing > 0)
	{
		printf("\nNot every test passed\n");
	}
	else
	{
		printf("All tests passed\n");
	}	
	
	printf("DONE TESTING ** Council Room Card ** FUNCTION \n\n");
	
	return 0;
	
}



































