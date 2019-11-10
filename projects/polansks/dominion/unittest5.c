#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>


/* This program will unit test the playBaron function that was created     */
/* when refactoring in Assignment 2                                         */

/************ Card Text *****************************************************/
/* You may discard an Estate for +4 coins. If you don't, gain an Estate     */
/****************************************************************************/


#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);


int main()
{
	printf("--------Testing playBaron function---------\n\n");

	struct gameState gameBase, gameBefore, gameAfter;

	int currentPlayer;
	int choice1; /* if this is 0, then an Estate has not been discarded and the player gains an Estate */
	currentPlayer = 0;

	initializeGameState(&gameBase);

	printf("Testing discarding an Estate\n");
	{
		choice1 = 1;

		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playBaron(choice1, &gameAfter);

		ASSERT(gameAfter.coins == gameBefore.coins + 4);
		ASSERT(gameAfter.discardCount[currentPlayer] = gameBefore.discardCount[currentPlayer] + 1);
		ASSERT(gameAfter.discard[currentPlayer][gameAfter.discardCount[currentPlayer] - 1] == estate);

		int i;
		int estateFlag = 0;
		for (i = 0; i < gameAfter.handCount[currentPlayer]; i++)
		{
			if (gameBefore.hand[currentPlayer][i] == estate)
			{
				estateFlag = 1;
			}

			if (estateFlag)
			{
				ASSERT(gameAfter.hand[currentPlayer][i] == gameBefore.hand[currentPlayer][i + 1]);
			}
			else
			{
				ASSERT(gameAfter.hand[currentPlayer][i] == gameBefore.hand[currentPlayer][i]);
			}
		}
	}

	printf("Testing not discarding an Estate\n");
	{
		choice1 = 0;

		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playBaron(choice1, &gameAfter);

		ASSERT(gameAfter.coins == gameBefore.coins);
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
