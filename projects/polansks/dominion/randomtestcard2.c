#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>

/* This file will do random testing for the Minion card */

/************ Card Text *****************************************************/
/* Choose one: +2; or discard your hand, +4 cards, and each other player    */
/* with at least 5 cards in hand discards their hand and draws 4 cards      */
/****************************************************************************/


#define BOOL int
#define TRUE 1
#define FALSE 0

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");


void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);

int randomInteger(int low, int high);
void checkAssertions(int trialNumber, int choice1, int returnValue, struct gameState *before, struct gameState *after);
int cardCount(struct gameState *s, int player, int cardType);


int main(int argc, char** argv)
{
	int i;
	int NUM_TRIALS = 5000;

	struct gameState stateBefore, stateAfter;
	PutSeed(2);

	for (i = 0; i < NUM_TRIALS; i++)
	{
		int choice1 = randomInteger(0, 1); /* This non-zero if +2 coins is chosen */
		int choice2 = !choice1; /* This is non-zero if discard hand/make other players redraw hand is chosen */

		initializeGameState(&stateBefore);
		stateBefore.hand[whoseTurn(&stateBefore)][0] = minion; /* Make sure they have a minion in their hand. Put it in the first spot */
		memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

		int returnValue = playMinion(choice1, choice2, &stateAfter, 0);

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

	int i;
	for (i = 0; i < numPlayers; i++)
	{
		if (i != whoseTurn(g))
		{
			g->handCount[i] = randomInteger(2, MAX_HAND);
		}
	}
	return;
}


void checkAssertions(int trialNumber, int choice1, int returnValue, struct gameState *before, struct gameState *after)
{
	printf("----Trial #%d-------\n", trialNumber);

	if (returnValue == -1)
	{
		ASSERT(memcmp(before, after, sizeof(struct gameState)) == 0);
		return;
	}

	int player = whoseTurn(before);

	ASSERT(after->numActions == before->numActions + 1);

	if (choice1)
	{
		/* If chose +2 coins, check that coins went up, hand count went down by one (for the discard) */
		ASSERT(after->handCount[player] == before->handCount[player] - 1);
		ASSERT(cardCount(after, player, minion) == cardCount(after, player, minion) - 1);
		ASSERT(after->coins == before->coins + 2);
	}
	else
	{
		/* Check that the current player only has 4 cards after discarding their hand and re-drawing */
		ASSERT(after->handCount[player] == 4);

		/* Make sure the discard pile is the correct size */
		if (before->deckCount[player] >= 4)
		{
			ASSERT(after->discardCount[player] == before->discardCount[player] + before->handCount[player]);
		}
		else
		{
			ASSERT(after->discardCount[player] == 4 - before->deckCount[player]);
		}

		/* Check the correct hand and discard pile size for the other players */
		int i;
		for (i = 0; i < before->numPlayers; i++)
		{
			if (before->handCount[i] >= 5 && i != player)
			{
				/* If they have 5 or more cards, make sure the hand changed correctly */
				ASSERT(after->handCount[i] == 4);

				if (before->deckCount[i] >= 4)
				{
					ASSERT(after->discardCount[i] == before->discardCount[i] + before->handCount[i]);
				}
				else
				{
					ASSERT(after->discardCount[i] == 4 - before->deckCount[i]);
				}
			}
			else if (i != player)
			{
				/* if they have 4 or fewer cards, make sure their hand didn't change */
				ASSERT(memcmp(after->hand[i], before->hand[i], sizeof(int) * MAX_HAND) == 0);
				ASSERT(memcmp(after->discard[i], before->discard[i], sizeof(int) * MAX_DECK) == 0);
			}
		}
	}

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