

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"

#define DEBUG 0

void testAssert(int exp, char* msg) {
	
	printf("%s: ", msg);
	if (exp)
		printf("\tPASSED\n");
	else
		printf("\tFAILED\n");
}

int main()
{

	printf("\n------------ TESTING TRIBUTE DUPLICATE REVEALED CARDS DOMINION BUG 9 ------------\n\n");
	

	// set your card array
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room };

	// declare the game state
	struct gameState G, g1;


	int p, r;
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

		enum CARD card = tribute;

		// set up variables for comparison
		int numActionsOrig = G.numActions;
		int numCoinsOrig = G.coins;
		int numHandOrig = G.handCount[curPlayer];

		// unit test -- two coppers
		/* 
		* Purpose: Revealed tribute cards are of same type. Ensure bonuses 
		* are awarded appropriately.
		* Setup and Expected results: 
		*				1. current player a tribute card, 0 coins
		*				2. next player has only treasure cards in their deck, last two cards are both copper
						3. current player gains 2 coins, no actions, and no additional cards
		*/

		// set up game state
		G.hand[curPlayer][0] = tribute;
		

		int nextPlayer = curPlayer + 1;
		if (nextPlayer > G.numPlayers) {
			nextPlayer = 0;
		}

		G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = copper;
		G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = copper;

		memcpy(&g1, &G, sizeof(struct gameState));

		updateCoins(whoseTurn(&G), &G, bonus);

		p = cardEffect(card, choice1, choice2, choice3, &G, handPos, &bonus); 

		updateCoins(whoseTurn(&G), &G, bonus);
		
		if (p >= 0) {

			printf("\n------------ TEST SCENARIO: TWO COPPERS REVEALED ------------\n");
			if (DEBUG) printf("Expected actions: %d\n", numActionsOrig);
			testAssert(numActionsOrig == G.numActions, "numActionsOrig == G.numActions");
			if (DEBUG) printf("Expected coins: %d\n", numCoinsOrig + 2);
			testAssert((numCoinsOrig + 2) == G.coins, "((numCoinsOrig + 2 ) == G.coins)");
			if (DEBUG) printf("Expected hand count: %d\n", numHandOrig);
			testAssert(numHandOrig == G.handCount[curPlayer], "numHandOrig == G.handCount[curPlayer]");
			printf("\n");

		}
		else {
			printf("cardEffect failure! Returned value: %d\n", p);

		}
		

		// second test: identical victory cards
		// there is a bug in the Tribute statement of cardEffect 
		// which decrements the deck count too many times while assigning revealed cards.
		// To isolate testing for the assigned bug, set more than necessary to be estate
		g1.deck[nextPlayer][g1.deckCount[nextPlayer] - 1] = estate;
		g1.deck[nextPlayer][g1.deckCount[nextPlayer] - 2] = estate;
		g1.deck[nextPlayer][g1.deckCount[nextPlayer] - 3] = estate;
		g1.deck[nextPlayer][g1.deckCount[nextPlayer] - 4] = estate;

		numActionsOrig	= g1.numActions;
		numCoinsOrig	= g1.coins;
		numHandOrig		= g1.handCount[curPlayer];

		p = cardEffect(card, choice1, choice2, choice3, &g1, handPos, &bonus);

		if (p >= 0) {
			printf("\n------------ TEST SCENARIO: TWO ESTATES REVEALED ------------\n");
			if (DEBUG) printf("Expected actions: %d\n", numActionsOrig);
			testAssert(numActionsOrig == g1.numActions, "numActionsOrig == g1.numActions");

			if (DEBUG) printf("Expected coins: %d\n", numCoinsOrig);
			testAssert(numCoinsOrig == g1.coins, "numCoinsOrig == g1.coins\t");

			if (DEBUG) printf("Expected hand count: %d\n", numHandOrig+2);
			testAssert(numHandOrig+2 == g1.handCount[curPlayer], "numHandOrig == g1.handCount[curPlayer]");
		}
		else {
			printf("cardEffect failure! Returned value: %d\n", p);
		}

	}


	return 0;
}