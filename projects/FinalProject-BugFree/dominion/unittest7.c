#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void assertFailed(char *file, int line);

int main(int argc, char** argv)
{

	// Had to fix the following line in cardEffect for tribute
	// Before:
	// state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
	// After:
	// state->deck[nextPlayer][state->deckCount[nextPlayer]] = -1;

	struct gameState stateBefore;
	struct gameState stateAfter;

	int currentPlayer = 0;
	int nextPlayer    = 1;

	stateBefore.numPlayers = 2;
	stateBefore.numActions = 2;

	stateBefore.whoseTurn = currentPlayer;
	stateBefore.handCount[currentPlayer] = 0;
	
	stateBefore.discardCount[nextPlayer] = 0;
	stateBefore.deckCount[nextPlayer] = 2;
	stateBefore.deck[nextPlayer][0] = copper;
	stateBefore.deck[nextPlayer][1] = adventurer;

	memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

	int bonus = 0;

	updateCoins(currentPlayer, &stateAfter, bonus);

	cardEffect(tribute, 0, 0, 0, &stateAfter, 0, &bonus);

	updateCoins(currentPlayer, &stateAfter, bonus);

	ASSERT(stateBefore.coins + 2 == stateAfter.coins);
	ASSERT(stateBefore.numActions + 2 == stateAfter.numActions);
	ASSERT(stateBefore.handCount[currentPlayer] == stateAfter.handCount[currentPlayer]);

	return 0;
}


void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}
