#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>

/* This file will do random testing for the Tribute card */

/************ Card Text *****************************************************/
/* The player to your left reveals then discards the top 2 cards of his     */
/* deck. For each differently named card revealed, if it is an...           */
/* Action Card, +2 actions                                                  */
/* Treasure Card, +2 coins                                                  */
/* Victory Card, +2 cards                                                   */
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
	int NUM_TRIALS = 1000;

	struct gameState stateBefore, stateAfter;
	PutSeed(2);

	for (i = 0; i < NUM_TRIALS; i++)
	{
		int choice1 = randomInteger(0, 1); /* if this is 0, then an Estate has not been discarded and the player gains an Estate */

		initializeGameState(&stateBefore);
		stateBefore.hand[whoseTurn(&stateBefore)][0] = tribute; /* Make sure they have a tribute in their hand */
		memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

		int nextPlayer = (whoseTurn(&stateAfter) == stateAfter.numPlayers - 1) ? 0 : whoseTurn(&stateAfter) + 1;
		int returnValue = tributeEffect(&stateAfter, whoseTurn(&stateAfter), nextPlayer);

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

	/* set a random player to be the current player */
	g->whoseTurn = randomInteger(0, g->numPlayers - 1);


	/* randomly assign the number of cards left in the next player's discard pile and deck */
	int nextPlayer = whoseTurn(g) == g->numPlayers - 1 ? 0 : whoseTurn(g) + 1;
	g->deckCount[nextPlayer] = randomInteger(0, g->deckCount[nextPlayer]);
	g->discardCount[nextPlayer] = randomInteger(0, g->discardCount[nextPlayer]);
	
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
	int nextPlayer = (player == before->numPlayers - 1) ? 0 : player + 1;

	if (before->deckCount[nextPlayer] >= 2)
	{
		int card1 = before->deck[nextPlayer][before->deckCount[nextPlayer] - 1];
		int card2 = before->deck[nextPlayer][before->deckCount[nextPlayer] - 2];

		int victory = isVictoryCard(card1) + isVictoryCard(card2);
		int treasure = isTreasureCard(card1) + isTreasureCard(card2);
		int action = 2 - victory - treasure;

		victory  = (victory  > 1) ? 1 : victory;
		treasure = (treasure > 1) ? 1 : treasure;
		action   = (action   > 1) ? 1 : action;

		ASSERT(after->numActions == before->numActions + action * 2);
		ASSERT(after->coins == before->coins + treasure * 2);
		ASSERT(after->handCount[player] == before->handCount[player] + victory * 2);

		if (before->deckCount[player] >= 2)
		{
			ASSERT(after->deckCount[player] == before->deckCount[player] - victory * 2);
		}
		else if (before->deckCount[player] == 1)
		{
			victory = victory > 1 ? 1 : victory;
			ASSERT(after->deckCount[player] == before->deckCount[player] - victory * 2);
		}

		ASSERT(after->deckCount[nextPlayer] == before->deckCount[nextPlayer]);
	}
	else if (before->deckCount[nextPlayer] + before->discardCount[nextPlayer]== 1)
	{
		int card1;
		if (before->deckCount[nextPlayer])
		{
			card1 = before->deck[nextPlayer][0];
		}
		else
		{
			card1 = before->discard[nextPlayer][0];
		}

		int victory = isVictoryCard(card1);
		int treasure = isTreasureCard(card1);
		int action = 1 - victory - treasure;

		ASSERT(after->numActions == before->numActions + action * 2);
		ASSERT(after->coins == before->coins + treasure * 2);
		ASSERT(after->handCount[player] == before->handCount[player] + victory * 2);
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