#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>


/* This program will unit test the mine Effect function that was created       */
/* when refactoring in Assignment 2                                         */

/************ Card Text *****************************************************/
/* You may trash a Treasure from your hand. Gain a Treasure to your hand    */
/* cost up to 3 more than it                                                */
/****************************************************************************/

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);
int cardsInHand(int cardType, int player, struct gameState *state);

int main()
{
	printf("--------Testing mineEffect function---------\n\n");

	struct gameState gameBase, gameBefore, gameAfter;

	int handPos = 0;
	int choice1; /* This is the index of the card being trashed in the player's hand. It must be a copper, silver or gold card. */
	int choice2; /* This is the card being gained. It must must be the value 4 (copper), 5 (silver) or 6 (gold) */
	int returnValue;
	int currentPlayer;

	initializeGameState(&gameBase);

	currentPlayer = 0;
	gameBase.hand[currentPlayer][handPos] = mine; /* set the card being played to be a mine */
	gameBase.whoseTurn = currentPlayer; // also set whose turn to be player 1


	printf("Testing invalid value for choice1 - trashing a Duchy card instead of a Treasure card\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		choice1 = 1;
		gameBefore.hand[currentPlayer][choice1] = duchy; /* Invalid value. Needs to be a treasure card. */
		choice2 = -1; /* Invalid value, but shouldn't matter because choice1 is invalid. */
		
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		returnValue = mineEffect(&gameAfter, choice1, choice2, whoseTurn(&gameAfter), handPos);

		/* Use asserts to check that the function has worked properly */
		/* In this case, the function should return -1 and no values in the game
		   state should change because invalid options were chosen */
		ASSERT(returnValue == -1);
		
		ASSERT(memcmp(&gameBefore, &gameAfter, sizeof(struct gameState)) == 0); /* the game state shouldn't have changed because we tried to play the card in an invalid way */
	}

	printf("Testing invalid value for choice2 - trying to gain a Treasure Map instead of a Treasure card\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		choice1 = 1;
		gameBefore.hand[currentPlayer][choice1] = copper;
		choice2 = treasure_map;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		returnValue = mineEffect(&gameAfter, choice1, choice2, whoseTurn(&gameAfter), handPos);

		/* Use asserts to check that the function has worked properly */
		/* In this case, the function should return -1 and no values in the game
		   state should change because invalid options were chosen */
		ASSERT(returnValue == -1);
		ASSERT(memcmp(&gameBefore, &gameAfter, sizeof(struct gameState)) == 0); /* the game state shouldn't have changed because we tried to play the card in an invalid way */
	}

	printf("Testing valid values - trashing a copper and gaining a silver\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		choice1 = 1;
		gameBefore.hand[currentPlayer][choice1] = copper;
		choice2 = silver;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		returnValue = mineEffect(&gameAfter, choice1, choice2, whoseTurn(&gameAfter), handPos);

		ASSERT(returnValue == 0);

		ASSERT(cardsInHand(copper, currentPlayer, &gameBefore) - 1 == cardsInHand(copper, currentPlayer, &gameAfter));
		ASSERT(cardsInHand(silver, currentPlayer, &gameBefore) + 1 == cardsInHand(silver, currentPlayer, &gameAfter));
		ASSERT(gameBefore.playedCardCount == gameAfter.playedCardCount);
	}


	return 0;
}

void initializeGameState(struct gameState *g)
{
	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randomSeed = 5;

	initializeGame(numPlayers, kingdomCards, randomSeed, g);

	return;
}

void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}

int cardsInHand(int cardType, int player, struct gameState *state)
{
	int i, count = 0;

	for (i = 0; i < state->handCount[player]; i++)
	{
		if (state->hand[player][i] == cardType)
		{
			count++;
		}
	}

	return count;
}
