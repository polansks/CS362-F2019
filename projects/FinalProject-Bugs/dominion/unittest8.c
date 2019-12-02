#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void assertFailed(char *file, int line);

void testBaron();
void testMinion();
void testTribute();
void testEmbargo();


int main(int argc, char** argv)
{
	testBaron();
	testMinion();
	testTribute();
	testEmbargo();
	return 0;
}

void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}

void testBaron()
{
	struct gameState stateBefore;
	struct gameState stateAfter;

	stateBefore.numPlayers = 1;
	stateBefore.handCount[0] = 2;
	stateBefore.hand[0][0] = baron;
	stateBefore.hand[0][1] = estate;
	stateBefore.numActions = 2;
	stateBefore.discardCount[0] = 0;

	stateBefore.whoseTurn = 0;

	updateCoins(0, &stateBefore, 0);

	memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

	playCard(0, 1, 0, 0, &stateAfter);

	ASSERT(stateBefore.coins + 4 == stateAfter.coins);

	return;
}

void testMinion()
{
	struct gameState stateBefore;
	struct gameState stateAfter;

	stateBefore.numPlayers = 1;
	stateBefore.handCount[0] = 1;
	stateBefore.hand[0][0] = minion;
	stateBefore.discardCount[0] = 0;
	stateBefore.playedCardCount = 0;

	stateBefore.whoseTurn = 0;

	updateCoins(0, &stateBefore, 0);

	memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

	playCard(0, 1, 0, 0, &stateAfter);

	ASSERT(stateBefore.coins + 2 == stateAfter.coins);
}

void testTribute()
{
	struct gameState stateBefore;
	struct gameState stateAfter;

	int currentPlayer = 0;
	int nextPlayer    = 1;

	stateBefore.numPlayers = 2;
	stateBefore.numActions = 2;

	stateBefore.whoseTurn = currentPlayer;
	stateBefore.handCount[currentPlayer] = 1;
	stateBefore.hand[currentPlayer][0] = tribute;
	
	stateBefore.discardCount[nextPlayer] = 0;
	stateBefore.deckCount[nextPlayer] = 2;
	stateBefore.deck[nextPlayer][0] = copper;
	stateBefore.deck[nextPlayer][1] = copper;

	stateBefore.playedCardCount = 0;

	memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

	updateCoins(currentPlayer, &stateAfter, 0);

	playCard(0, 0, 0, 0, &stateAfter);

	ASSERT(stateBefore.coins + 2 == stateAfter.coins);

}

void testEmbargo()
{
	struct gameState stateBefore;
	struct gameState stateAfter;

	stateBefore.whoseTurn = 0;

	int choice1 = adventurer;
	stateBefore.supplyCount[choice1] = 1;;

	stateBefore.handCount[0] = 1;
	stateBefore.hand[0][0] = embargo;
	stateBefore.playedCardCount = 0;

	memcpy(&stateAfter, &stateBefore, sizeof(struct gameState));

	playCard(0, choice1, 0, 0, &stateAfter);

	ASSERT(stateBefore.coins + 2 == stateAfter.coins);
}