#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>

/* This file will do random testing for the Baron card */

/************ Card Text *****************************************************/
/* You may discard an Estate for +4 coins. If you don't, gain an Estate     */
/****************************************************************************/

#define BOOL int
#define TRUE 1
#define FALSE 0

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");


void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);

int randomInteger(int low, int high);
void checkAssertions(int trialNumber, BOOL discardedEstate, int returnValue, struct gameState *before, struct gameState *after);
int cardCount(struct gameState *s, int player, int cardType);

int main(int argc, char** argv)
{
	int i;
	int NUM_TRIALS = 5000;

	struct gameState stateBefore, stateAfter;
	PutSeed(2);

	for (i = 0; i < NUM_TRIALS; i++)
	{
		int choice1 = randomInteger(0, 1); /* if this is 0, then an Estate has not been discarded and the player gains an Estate */

		initializeGameState(&stateBefore);

		stateBefore.hand[whoseTurn(&stateBefore)][0] = baron; /* assign a baron to the fist card in the player's hand */

		memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

		int returnValue = playBaron(choice1, &stateAfter);

		checkAssertions(i, choice1, returnValue, &stateBefore, &stateAfter);

	}
	return 0;
}


void initializeGameState(struct gameState *g)
{
	int numPlayers = randomInteger(2, 4);
	
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randomSeed = randomInteger(1, 9999999);

	initializeGame(numPlayers, kingdomCards, randomSeed, g);

	return;
}

void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}

int randomInteger(int low, int high)
{
	return Random() * (high - low + 1) + low;
}


void checkAssertions(int trialNumber, BOOL discardedEstate, int returnValue, struct gameState *before, struct gameState *after)
{
	printf("----Trial #%d-------\n", trialNumber);

	if (returnValue == -1)
	{
		ASSERT(memcmp(before, after, sizeof(struct gameState)) == 0);
		return;
	}

	int player = whoseTurn(before);

	ASSERT(cardCount(after, player, baron) == cardCount(before, player, baron) - 1); // 1 fewer baron
	ASSERT(after->numBuys == before->numBuys + 1);

	if (discardedEstate && cardCount(before, player, estate) > 0)
	{
		ASSERT(after->coins == (before->coins + 4));// 4 more coins
		ASSERT(cardCount(after, player, estate) == cardCount(before, player, estate) - 1); // 1 fewer estate
		ASSERT(after->handCount[player] == before->handCount[player] - 2);
		ASSERT(after->discardCount[player] == before->discardCount[player] + 1);
		ASSERT(after->discard[player][after->discardCount[player] - 1] == estate);
	}
	else
	{
		ASSERT(after->coins == before->coins);

		if (before->supplyCount[estate] > 0)
		{
			ASSERT(cardCount(after, player, estate) == cardCount(before, player, estate) + 1); // 1 more estate
			ASSERT(after->handCount[player] == before->handCount[player]);
			ASSERT(after->supplyCount[estate] == before->supplyCount[estate] - 1);
		}
	}

	return;
}

int cardCount(struct gameState *s, int player, int cardType)
{
	int i, count = 0;
	for (i = 0; i < s->handCount[player]; i++)
	{
		if (s->hand[player][i] == cardType)
		{
			count++;
		}
	}

	return count;
}