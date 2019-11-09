#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>


/* This program will unit test the playMinion function that was created     */
/* when refactoring in Assignment 2                                         */

/************ Card Text *****************************************************/
/* Choose one: +2; or discard your hand, +4 cards, and each other player    */
/* with at least 5 cards in hand discards their hand and draws 4 cards      */
/****************************************************************************/

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);

int main()
{
	printf("--------Testing playMinion function---------\n\n");

	struct gameState gameBase, gameBefore, gameAfter;

	int handPos = 0;
	int choice1; /* This non-zero if +2 coins is chosen */
	int choice2; /* This is non-zero if discard hand/make other players redraw hand is chosen */
	int returnValue;
	int currentPlayer, otherPlayer;

	initializeGameState(&gameBase);

	currentPlayer = 0;
	otherPlayer = 1;
	gameBase.hand[currentPlayer][handPos] = minion; /* set the card being played to be a Minion */
	gameBase.whoseTurn = currentPlayer; // also set whose turn to be player 1

	printf("Testing option of +2 coins\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		choice1 = 1;
		choice2 = 0;
		returnValue = playMinion(choice1, choice2, &gameAfter, handPos);

		ASSERT(returnValue == 0);
		ASSERT(memcmp(gameBefore.hand[otherPlayer], gameAfter.hand[otherPlayer], sizeof(int) * MAX_HAND) == 0); /* the hand should be the same for the other player */
		ASSERT(gameBefore.coins + 2 == gameAfter.coins);
	}

	printf("Testing option of redrawing hand and other player has 5 cards\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		choice1 = 0;
		choice2 = 1;
		returnValue = playMinion(choice1, choice2, &gameAfter, handPos);

		ASSERT(returnValue == 0);
		ASSERT(gameAfter.handCount[currentPlayer] == 4);
		ASSERT(memcmp(gameAfter.hand[otherPlayer], gameBefore.hand[otherPlayer], sizeof(int) * MAX_HAND) != 0);
	}

	printf("Testing option of redrawing hand and other player has 4 cards\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		gameBefore.handCount[otherPlayer] = 4; /* make the other player have four cards in their hand */ 

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		choice1 = 0;
		choice2 = 1;
		returnValue = playMinion(choice1, choice2, &gameAfter, handPos);

		ASSERT(returnValue == 0);
		ASSERT(gameAfter.handCount[currentPlayer] == 4);
		ASSERT(memcmp(gameAfter.hand[otherPlayer], gameBefore.hand[otherPlayer], sizeof(int) * MAX_HAND) == 0);
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