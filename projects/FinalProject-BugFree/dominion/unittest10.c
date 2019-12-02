

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

void testAssert(int exp, char* msg) {
	
	printf("%s: ", msg);
	if (exp)
		printf("\tPASSED\n");
	else
		printf("\tFAILED\n");
}

int main()
{

	printf("\n------------ TESTING AMBASSADOR DISCARD CORRECT CARDS DOMINION BUG 10 ------------\n\n");
	

	// set your card array
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// declare the game state
	struct gameState G;

	int i, p, r;
	int seed = 44;

	// set up random numbers
	SelectStream(2);

	PutSeed(3);

	// set r to known value
	r = -5;

	// initialize game
	r = initializeGame(2, k, seed, &G);
	
	if (r < 0)
	{
		printf("!!!GAME INITIALIZATION FAILED!!!\n");
	}
	else
	{
		// set up variables for function to be called
		int handPos = 0;
		int curPlayer = 0;
		int choice1 = 0;
		int choice2 = 0;
		int choice3 = 0;
		int bonus = 0;

		enum CARD card = ambassador;

		// unit test -- discard two mine cards
		/*
		* Scenario: current player chooses to reveal a mine card in their hand.
		* They have 2 total in their hand. Player 2 has no copies of this card
		* Expected results:
		*				1. current player has no mine cards in their hand
		*				2. next player has 1 more card in their discard and it is of type 'mine'
						3. Supply of mine cards increases by 1 (cur player -2, +1 next player = +1 to put in supply
		*/

		// set up game state
		G.hand[curPlayer][0] = card;
		
		G.hand[curPlayer][1] = mine;
		G.hand[curPlayer][2] = duchy;
		G.hand[curPlayer][3] = copper;
		G.hand[curPlayer][4] = mine;
		
		G.whoseTurn = curPlayer;
		G.handCount[curPlayer] = 5;

		int nextPlayer = curPlayer + 1;
		if (nextPlayer > G.numPlayers) {
			nextPlayer = 0;
		}


		// set up player variables to pass
		choice1 = 1; // type to discard is in position 1
		choice2 = 1; // additional amount to discard

		p = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus); 

		if (p >= 0) {

			// check expected results
			int mineFound = 0;

			// check that next player has mine in their discard
			for (i = 0; i < G.discardCount[nextPlayer]; i++)
			{
				if (G.discard[nextPlayer][i] == mine)
				{
					mineFound = 1;
				}
			}

			printf("\n------------ TEST SCENARIO: MINE CARD TRASHED (x2) ------------\n");
			
			testAssert(mineFound == 1, "nextPlayer mineFound == 1");
			
			mineFound = 0;
			// check that current player does not have mine in hand or discard
			for (i = 0; i < G.discardCount[curPlayer]; i++)
			{
				if (G.discard[curPlayer][i] == mine)
				{
					mineFound = 1;
				}
			}
			testAssert(mineFound == 0, "curPlayer mineFound == 0");

			printf("\n");
		}
		else {
			printf("cardEffect failure! Returned value: %d\n", p);
		}
	}


	return 0;
}